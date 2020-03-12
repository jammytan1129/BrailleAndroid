/*
 * Copyright (C) 2015 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package com.fyp.jammytan.test.display;

import com.fyp.jammytan.test.R;
import com.fyp.jammytan.test.display.BrailleDisplayProperties;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.res.Resources;
import android.os.ParcelUuid;
import android.util.Log;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Collections;
import java.util.List;
import java.util.Set;

/**
 * The thread that connects to a device that it finds, reads from the device
 * and starts another thread that manages the driver.
 */
class ReadThread extends Thread implements DriverThread.OnInitListener {
    private static final String LOG_TAG = ReadThread.class.getSimpleName();

    private final DisplayService mDisplayService;
    private final DeviceFinder mDeviceFinder;
    private final File mTablesDir = null;
    private final String mBluetoothAddressToConnectTo;
    private final Resources mResources;
    private volatile BluetoothSocket mSocket;
    private volatile boolean mDisconnecting;
    private volatile DriverThread mDriverThread;
    private volatile DeviceFinder.DeviceInfo mConnectedDeviceInfo;


    /**
     * Constructs the thread so that it can be started.
     * {@code displayService} will get called when the display is either
     * connected or disconnected.  {@code tablesDir} is a directory that
     * contains keyboard tables and is forwarded to the driver thread.
     * {@code bluetoothAddressToConnectTo}, if non-null, makes the connection
     * process only consider a device with the give bluetooth address.
     */
    public ReadThread(DisplayService displayService,
            String bluetoothAddressToConnectTo) {
        mDisplayService = displayService;
        mDeviceFinder = new DeviceFinder(displayService);
        //mTablesDir = tablesDir;
        mBluetoothAddressToConnectTo = bluetoothAddressToConnectTo;
        mResources = displayService.getResources();
    }

    @Override
    public void run() {
        try {
            if (connect()) {
                 readLoop();
            }
        } finally {
            cleanup();
        }
    }

    /** Returns the driver thread, or null if not connected. */
    public DriverThread getDriverThread() {
        return mDriverThread;
    }

    /**
     * Asynchronously disconnects, which will eventually lead to the
     * thread terminating.  If not connected yet, the attempts to connect
     * to a display will be aborted.  Calls back into
     * {@link DisplayService#onDisplayDisconnected} before dying.
     */
    public void disconnect() {
        // Close the socket to abort any blocking operations.
        closeSocket();
        mDisconnecting = true;
    }
    private void connectMyDevice(){
        BluetoothAdapter adapter = BluetoothAdapter.getDefaultAdapter();
        Set<BluetoothDevice> bondedDevices = adapter.getBondedDevices();
        BluetoothDevice device;
        ParcelUuid[] uuids;
        if (bondedDevices.size()>0) {
            mSocket = null;
            try {
                int count = 0;
                for (BluetoothDevice dev : bondedDevices) {
                    String deviceName = dev.getName();
                    if (deviceName.equals("514")) {
                        break;
                    }
                    count++;
                }
                Object[] devices = bondedDevices.toArray();
                device = (BluetoothDevice) devices[count];
                uuids = device.getUuids();
                mDisplayService.setConnectionProgress(
                        mResources.getString(R.string.connprog_trying,
                                device.getName()));
                Log.e(LOG_TAG, "trying get device");
                try {
                    BluetoothSocket socket;
                    socket = device.createRfcommSocketToServiceRecord(uuids[0].getUuid());
                    //adapter.cancelDiscovery();
                    if (socket != null) {
                        mDisplayService.setConnectionProgress(
                                mResources.getString(R.string.connprog_socket_not_null));
                        Log.e(LOG_TAG, "socket not null");
                        socket.connect();
                        mSocket= socket;
                        Log.e(LOG_TAG, "socket connected ");
                        OutputStream oStream = mSocket.getOutputStream();
                        oStream.write("Connected".getBytes());
                        Log.e(LOG_TAG, "send test");
                        mConnectedDeviceInfo = new DeviceFinder.DeviceInfo(device, null, uuids[0].getUuid(), false, null);
                    }

                } catch (IOException ex) {
                    try {
                        mSocket.close();
                        Log.e(LOG_TAG, "socket closed");
                    } catch (IOException closeException) { }
                    mDisplayService.setConnectionProgress(
                            mResources.getString(R.string.connprog_connect_fails));
                    Log.e(LOG_TAG, "Error opening a socket: " + ex.toString());
                }
            }finally {
                Log.e(LOG_TAG, "In finally ");
        }
//            finally {
//                if (mSocket == null) {
//                    mDisplayService.setConnectionProgress(null);
//                }
//            }
        }

    }
    private boolean connect() {
        List<DeviceFinder.DeviceInfo> bonded = mDeviceFinder.findDevices();
        if (bonded.size() > 0) {
            tryToConnect(bonded);
        } else {
            connectMyDevice();
            //mDisplayService.setConnectionProgress(
            //        mResources.getString(R.string.connprog_no_devices));
        }
        if (mSocket != null) {
            BluetoothDevice bthDev = mConnectedDeviceInfo.getBluetoothDevice();
            mDisplayService.setConnectionProgress(
                    mResources.getString(R.string.connprog_initializing,
                            bthDev.getName()));
            try {
                mDriverThread = new DriverThread(mSocket.getOutputStream(),
                        mConnectedDeviceInfo,
                        mResources,
                        //mTablesDir,
                        this /*initListener*/,
                        mDisplayService /*inputEventListener*/);
                Log.i(LOG_TAG, "Device connected");
                return true;
            } catch (IOException ex) {
                Log.e(LOG_TAG, "Error while starting driver thread", ex);
            }
        }
        return false;
    }

    private void readLoop() {
        try {
            byte[] buf = new byte[128];
            int readSize;
            do {
                readSize = mSocket.getInputStream().read(buf, 0, buf.length);
                if (readSize > 0) {
                    // Enqueue the input which will eventually wake up the
                    // driver to poll for this data.
                    mDriverThread.addReadOperation(buf, readSize);
                }
            } while (readSize >= 0);
            Log.i(LOG_TAG, "End of input from device.");
        } catch (IOException ex) {
            Log.i(LOG_TAG, "Socket closed while reading: " + ex);
        }
    }

    private void tryToConnect(List<DeviceFinder.DeviceInfo> bonded) {
        mSocket = null;
        try {
            for (DeviceFinder.DeviceInfo dev : bonded) {
                if (mDisconnecting) {
                    return;
                }
                BluetoothDevice bthDev = dev.getBluetoothDevice();
                if (mBluetoothAddressToConnectTo != null
                        && !mBluetoothAddressToConnectTo.equals(
                                bthDev.getAddress())) {
                    continue;
                }
                mDisplayService.setConnectionProgress(
                        mResources.getString(R.string.connprog_trying,
                                bthDev.getName()));
                Log.d(LOG_TAG, "Trying to connect to braille device: "
                        + bthDev.getName());
                try {
                    BluetoothSocket socket;
                    if (dev.getConnectSecurely()) {
                        socket = bthDev
                                .createRfcommSocketToServiceRecord(
                                        dev.getSdpUuid());
                    } else {
                        socket = bthDev
                                .createInsecureRfcommSocketToServiceRecord(
                                        dev.getSdpUuid());
                    }
                    if (socket != null) {
                        socket.connect();
                        mSocket = socket;
                        mConnectedDeviceInfo = dev;
                    }
                    return;
                } catch (IOException ex) {
                    Log.e(LOG_TAG, "Error opening a socket: " + ex.toString());
                }
            }
        } finally {
            if (mSocket == null) {
                mDisplayService.setConnectionProgress(null);
            }
        }
    }

    private void closeSocket() {
        // More than one calls of this function is allowed, even in paralell
        // because close on the socket is idempotent.
        if (mSocket != null) {
            try {
                mSocket.close();
            } catch (IOException ex) {
                Log.d(LOG_TAG, "Error closing socket: ", ex);
            }
        }
    }

    private void cleanup() {
        closeSocket();
        if (mDriverThread != null) {
            DriverThread localDriverThread = mDriverThread;
            mDriverThread = null;
            localDriverThread.stop();
        }
        mDisplayService.onDisplayDisconnected();
        Log.i(LOG_TAG, "Display disconnected");
    }

    @Override
    public void onInit(BrailleDisplayProperties properties) {
        // We're in the driver thread.
        if (properties != null) {
            mDeviceFinder.rememberSuccessfulConnection(mConnectedDeviceInfo);
            mDisplayService.setConnectionProgress(null);
            mDisplayService.onDisplayConnected(properties);
        } else {
            BluetoothDevice bthDev = mConnectedDeviceInfo.getBluetoothDevice();
            mDisplayService.setConnectionProgress(
                    mResources.getString(
                            R.string.connprog_failed_to_initialize,
                            bthDev.getName()));
            disconnect();
            return;
        }
    }
}
