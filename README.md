
# examine-IME-support-Racket

examine IME support in the Racket onto Windows

Windows上のRacketでのIMEサポートの調査

## gtk3.0とpango のサンプル実装

Pangoはテキストレイアウトとレンダリングのライブラリーで、多言語の同時表示などに対応しています。

- [hello_gtk.c](hello_gtk.c) は、GTK+3.0のHelloworld
- [gtk3_0_with_pango.c](gtk3_0_with_pango.c) は、Pangoでテキストを用意してGTK+3.0上で表示

## **問題**Racketのtext% エディターはIMEをサポートしていません。
