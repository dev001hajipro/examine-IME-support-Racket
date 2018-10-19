
# examine-IME-support-Racket

examine IME support in the Racket onto Windows

これは、Window10のDrRacketで日本語入力時に、補完候補がデスクトップ上に表示されるので、対応できるか調べているときのメモです。

## 問題:Racketの text% テキストエディターオブジェクトは一般的なIMEをサポートしていない

入力補完がアプリケーション上ではなくデスクトップ上に表示されます。よって日本語を入力しようとすると
画面左上に表示される入力候補とDrRacketの入力先キャレットを交互に見るのでとてもストレスになります。

そこで、Windows上のRacketでのIMEサポートがどのようになっているのか調べてみました。

## Racketでシンプルなテキストエディターを作ってIMEの動きを確認

[ime_input.rkt](ime_input_rkt) は、text%オブジェクトを使ったシンプルなテキストエディターです。
これでも補完候補がデスクトップ上に表示されました。

よって、**DrRacket IDEだけではなく、Racketのtext%オブジェクト自体が一般的なIMEの動きをしていない**事が分かりました。

## Racketをソースコードからビルド

Racket本体のビルドとmain-distributionのDrRacketのビルド方法

[BuildRacketWindows10.md](BuildRacketWindows10.md)

## ビルドエラー時に調べたracketとracoの各種オプション

`-l-`の意味などもここで説明しています。

[memo-raco-command.md](memo-raco-command.md)

## Native LibraryとDLLを調査

DrRacketのソースコードを調べてmessage-boxなどを表示できるようになりましたが、IMEの動きに関連するコードを見つけられないので
NativeLibraryについて調べます。

```racket
; デバッグのためメッセージボックスを埋め込んでみる
(message-box "hello" "test messagebox" #f '(ok))
```

[native-library-and-dll.md](native-library-and-dll.md)

## gtk3.0とpango のサンプル実装

Pangoはテキストレイアウトとレンダリングのライブラリーで、多言語の同時表示などに対応しています。

- [hello_gtk.c](hello_gtk.c) は、GTK+3.0のHelloworld
- [gtk3_0_with_pango.c](gtk3_0_with_pango.c) は、Pangoでテキストを用意してGTK+3.0上で表示



## TODO
- 入力補完候補ダイアログの正式名称。composite???
