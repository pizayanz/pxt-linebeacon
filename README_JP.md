# LINE Beacon for micro:bit

[English is here (英語はこちら)](README.md)

## Version 依存

### for micro:bit v2

この LINE Beacon 拡張機能は、Bluetooth 拡張機能と排他的なため、一緒に動作させることはできません。

ご利用の場合は、プロジェクトから Bluetooth 拡張機能を取り除いてください。

### for micro:bit v1

この LINE Beacon 拡張機能を動かすためには、Bluetooth 拡張機能が必要です。

ご利用の場合は、プロジェクトに Bluetooth 拡張機能を追加してください。


## 使い方

これは、micro:bit を LINE Beacon 化するパッケージです

## LINE Beacon とは

LINE Beacon とは、Android や iOS にインストールされた LINEアプリと連動し、さまざまな動作をさせることができる IoT デバイスです。

店舗に LINE Beacon を置いておけば、それに近づいた方に、自動的に LINEでクーポンを送ったり、店舗情報を送ったりすることができます。

[https://developers.line.me/ja/docs/messaging-api/using-beacons/](https://developers.line.me/ja/docs/messaging-api/using-beacons/)

## Quick Start

1. 最初に LINE に登録し、あなた専用の HWID を入手してください [https://admin-official.line.me/beacon/register](https://admin-official.line.me/beacon/register)
1. このパッケージを micro:bit の Javascript Block Editor に追加し、'LINE Beacon start' ブロックを配置、入手した HWID (5 bytes hex) をそこにコピー＆ペーストするだけでご利用いただけます

最初のコンパイルには数分かかるケースがあります

## Sample

```blocks
input.onButtonPressed(Button.A, function () {
    basic.showIcon(IconNames.Yes)
    linebeacon.start("0f0f0f0f0f")
})
input.onButtonPressed(Button.AB, function () {
    basic.showIcon(IconNames.Yes)
    linebeacon.startWithDeviceMessage(
    "0f0f0f0f0f",
    "1a2b3c4d5e6f70809010a0b0c0"
    )
})
input.onButtonPressed(Button.B, function () {
    basic.showIcon(IconNames.No)
    linebeacon.stop()
})
basic.showIcon(IconNames.Heart)
```

## License

MIT

## Supported targets

* for PXT/microbit

<script src="https://makecode.com/gh-pages-embed.js"></script><script>makeCodeRender("{{ site.makecode.home_url }}", "{{ site.github.owner_name }}/{{ site.github.repository_name }}");</script>

