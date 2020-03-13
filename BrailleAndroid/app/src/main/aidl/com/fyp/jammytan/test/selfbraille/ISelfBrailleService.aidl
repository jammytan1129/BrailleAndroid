// ISelfBrailleService.aidl
package com.fyp.jammytan.test.selfbraille;

// Declare any non-default types here with import statements

import com.fyp.jammytan.test.selfbraille.WriteData;

/**
 * Interface for a client to control braille output for a part of the
 * accessibility node tree.
 */
interface ISelfBrailleService {
    void write(IBinder clientToken, in WriteData writeData);
    oneway void disconnect(IBinder clientToken);
}
