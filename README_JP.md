# LINE Beacon for micro:bit

[English is here (英語はこちら)](README.md)

## 使い方

これは、micro:bit を LINE Beacon 化するパッケージです

## LINE Beacon とは

LINE Beacon とは、Android や iOS にインストールされた LINEアプリと連動し、さまざまな動作をさせることができる IoT デバイスです。

店舗に LINE Beacon を置いておけば、それに近づいた方に、自動的に LINEでクーポンを送ったり、店舗情報を送ったりすることができます。

https://developers.line.me/ja/docs/messaging-api/using-beacons/

## Quick Start

1. 最初に LINE に登録し、あなた専用の HWID を入手してください https://admin-official.line.me/beacon/register
1. このパッケージを micro:bit の Javascript Block Editor に追加し、'LINE Beacon start' ブロックを配置、入手した HWID (5 bytes hex) をそこにコピー＆ペーストするだけでご利用いただけます

最初のコンパイルには数分かかるケースがあります

## Sample

![Sample](./docs/LINEBeaconSample.png "Sample")

## License

MIT

## Supported targets

* for PXT/microbit
(The metadata above is needed for package search.)

