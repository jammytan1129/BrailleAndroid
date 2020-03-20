# Braille Keyboard
###### tags: `106年專題`
[TOC]
## Introduction
- Braille Keyboard是一個輕巧、方便攜帶且操作簡單的視障人士專用的盲人智能點字鍵盤。
- Braille Keyboard主要有兩項功能：
    - 透過視障人士所熟悉的點字輸入法進行輸入，將文字顯示在使用者所使用的APP裡的輸入元件上。
    - 當使用者進行輸入或是點擊畫面上的文字或元件時，Arduino鍵盤將文字逐一顯示在點字顯示器上。
- Braille Keyboard主要基於Google的BrailleBack無障礙服務並結合了Arduino所開發，通過藍芽連結進行訊號傳遞。
- Braille Keyboard概念圖
![](https://i.imgur.com/2qTGnxP.png)

## Arduino Keyboard
- Braille Keyboard的鍵盤所使用的主控板為Arduino Mega2560，搭配1個HC-05藍芽模組，12顆按鈕，6顆電磁閥及3組兩路繼電器所組成。
- 硬體鍵盤的按鍵功能：
<img src="https://i.imgur.com/G0uXM3L.png" alt="Arduino Keyboard" title="Arduino Keyboard" width="300" />

## Android Accessibility Service
- 打開行動裝置藍芽及開啟硬體鍵盤，並以藍芽的方式進行連結。
<img src="https://i.imgur.com/x9XlPlT.png" alt="Connect Keyboard" title="Connect Keyboard" width="200" />
- 在安裝Braille Android後，可在行動裝置上的Setting->Accessibility中找到Braille Keyboard服務。
<img src="https://i.imgur.com/l5DQ4QT.png" alt="Find Braille Keyboard Service" title="Find Braille Keyboard Service" width="200" />
-  使用者可以進入Braille Keyboard中的Setting檢查是否有連接上硬體鍵盤。
<img src="https://i.imgur.com/b6gBvyG.png" alt="Check Braille Keyboard Connected" title="Check Braille Keyboard Connected" width="200" />
- 在使用Braille Keyboard之前，須先打開TalkBack功能，才能夠使用硬體鍵盤中的點字顯示功能。
<img src="https://i.imgur.com/cyanb4m.png" alt="Switch on TalkBack Service" title="Switch on TalkBack Service" width="200" />

## Braille Input Method
- 點字輸入是由6點組成:
    - 左手食指的位置開始到左手無名指，依序為1、2和3
    - 右手食指的位置開始到右手無名指依序為4、5和6
    - 左右手尾指的按鍵分別為換行鍵及倒退鍵
    - 左右手拇指的按鍵分別為空白鍵及語言轉換鍵
    - 另外，右下方的兩顆功能為閱讀上一字和下一字的按鍵
    - <img src="https://i.imgur.com/b4xrL7F.png" alt="Braille" title="Braille" width="100" /> <img src="https://i.imgur.com/W2MSHfH.png" alt="Braille Keyboard" title="Braille Keyboard" width="300" />
- 盲文點字的拉丁字母 a – z 是目前最普遍使用到的基礎點字文字，其中的 a – j 與羅馬數字 1 – 0 相同。
![](https://i.imgur.com/v7UluWZ.png)
- 若要輸入數字，則在輸入數字之前先輸入前置符號
    - 前置符號： <img src="https://i.imgur.com/RaJBWGe.png" alt="pre-number sign" title="pre-number sign" width="30" />
![](https://i.imgur.com/d0MQMBx.png)
- 字母大小寫
    - 前置符號： <img src="https://i.imgur.com/v7lR4rw.png" alt="Capital Sign" title="Capital Sign" width="25" />
    - 若只要單一字母大寫，只須在輸入字母之前輸入**一次**前置符號
    - 若要整個字大寫，則輸入字母前輸入**兩次**前置符號
    - 每當使用者輸入換行鍵，空白鍵及語言轉換鍵，就會取消大寫符號
- 符號

    | 符號 | 點字 | 符號 | 點字 | 符號 | 點字 | 符號 | 點字 |
    | -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |
    | , | ![](https://i.imgur.com/0W3L3M3.png=25x)| = | ![](https://i.imgur.com/9IORLhx.png=45x) | < | ![](https://i.imgur.com/xbAo01s.png=45x) | # | ![](https://i.imgur.com/jBEAahQ.png=45x) |
    | . |![](https://i.imgur.com/Ls847tJ.png=25x) | \` | ![](https://i.imgur.com/GOuJshy.png=45x) | > | ![](https://i.imgur.com/1vG8ZeI.png=45x) | \| | ![](https://i.imgur.com/fXmVTPj.png=45x) |
    | ; | ![](https://i.imgur.com/AOOJVqh.png=25x) | ? | ![](https://i.imgur.com/xFnhB1E.png=25x) | ( | ![](https://i.imgur.com/IUjY8T6.png=45x) | ~ | ![](https://i.imgur.com/SR0mzwk.png=45x) |
    | ' | ![](https://i.imgur.com/XtbuGLm.png=25x) | ! | ![](https://i.imgur.com/4jxT8p8.png=25x) | ) | ![](https://i.imgur.com/lZYvdYw.png=45x) | $ | ![](https://i.imgur.com/9T8DmW9.png=45x) |
    | \ | ![](https://i.imgur.com/AxJp0vm.png=45x) | : | ![](https://i.imgur.com/XO2CL3s.png=25x) | [ | ![](https://i.imgur.com/4O61Ncq.png=45x) | % | ![](https://i.imgur.com/Xu6R9gu.png=45x) |
    | / | ![](https://i.imgur.com/qv43PC6.png=45x) | “ | ![](https://i.imgur.com/Z0xdh0O.png=45x) | ] | ![](https://i.imgur.com/y1GH00k.png=45x) | _ | ![](https://i.imgur.com/8IZXO5k.png=45x) |
    | - | ![](https://i.imgur.com/tWauIJX.png=45x) | ” | ![](https://i.imgur.com/e7WS1Mm.png=45x) | { | ![](https://i.imgur.com/1NmoAV8.png=45x) | + | ![](https://i.imgur.com/9un1XSr.png=45x) |
    | * | ![](https://i.imgur.com/syTRsVI.png=45x) | @ | ![](https://i.imgur.com/GRMgpbB.png=45x) | } | ![](https://i.imgur.com/wLtJOEy.png=45x) | & | ![](https://i.imgur.com/lSg5SVq.png=45x) |
