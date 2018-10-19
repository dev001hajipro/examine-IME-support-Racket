
# examine-IME-support-Racket

examine IME support in the Racket onto Windows

これは、Window10のDrRacketで日本語入力時に、補完候補がデスクトップ上に表示されるので、対応できるか調べているときのメモです。

## Racketの text% テキストエディターオブジェクトは一般的なIMEをサポートしていない問題

入力補完がアプリケーション上ではなくデスクトップ上に表示されます。よって日本語を入力しようとすると
画面左上に表示される入力候補とDrRacketの入力先キャレットを交互に見るのでとてもストレスになります。

そこで、Windows上のRacketでのIMEサポートがどのようになっているのか調べてみました。

## gtk3.0とpango のサンプル実装

Pangoはテキストレイアウトとレンダリングのライブラリーで、多言語の同時表示などに対応しています。

- [hello_gtk.c](hello_gtk.c) は、GTK+3.0のHelloworld
- [gtk3_0_with_pango.c](gtk3_0_with_pango.c) は、Pangoでテキストを用意してGTK+3.0上で表示

## Racketで実装したシンプルなテキストエディターでIMEの動きを確認

[ime_input.rkt](ime_input_rkt) は、text%オブジェクトを使ったシンプルなテキストエディターです。
このシンプルなテキストエディターでも、やはり補完候補がデスクトップ上に表示されます。

よって、**DrRacketの補完候補というよりも、Racketのtext%オブジェクト自体が一般的なIMEをサポートしていないことが分かりました。**

## Racketをソースコードからビルド

Racket本体のビルドとmain-distributionのDrRacketのビルド方法

[BuildRacketWindows10.md](BuildRacketWindows10.md)

## ビルドエラー時に調べたracketとracoの各種オプション

`-l-`の意味などもここで説明しています。

[memo-raco-command.md](memo-raco-command.md)

## TODO
- 入力補完候補ダイアログの正式名称。composite???
