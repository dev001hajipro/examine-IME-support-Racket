# Native LibraryとDLL

Windows 64bit版のnative libraryは、<https://github.com/racket/libs> でビルド済みで公開されています。
Racketライブラリーからこれらnative libraryを呼び出して描画などを行うのでいくつかライブラリーを調べてみます。

## draw-lib:[The Racket Drawing Toolkit](https://docs.racket-lang.org/draw/index.html) を調べる

Racketで線を表示する場合は、`(reqire racket/draw)`で使えるようになります。公式マニュアルを見ると `package: [draw-lib](https://pkgs.racket-lang.org/package/draw-lib)`
とリンクがあり、リンク先の情報から、ソースコードが<https://github.com/racket/draw/tree/master/draw-lib>にある事が分かります。

[unsafe](https://github.com/racket/draw/tree/master/draw-lib/racket/draw/unsafe)ディレクトリー一覧を見てみると、
glib.rktが見つかりました。ffi-lib関数でWindowsのDLLとRacketを繋げているのが確認できます。

また、pango.rktやcairo.rktもあります。ffi-libを調べていくことでRacketとNativeLibraryの連携方法が理解できそうです。

## Racket実行に必要なビルド済みライブラリー <https://github.com/racket/libs>

ここには、各種OS事に必要なビルド済みライブラリーがあります。これらはnmakeを実行したときに、Racketのソースコードをビルド後、
ダウンロードするようです。(raco setup)

# draw-win32-x86_64-3

<https://github.com/racket/libs/tree/master/draw-win32-x86_64-3/racket/draw> を見ると、必要なDLLが確認できます。

これらは、Racketビルド後のracket/racket/libに置いてあるのも確認できます。

[info.rkt](https://github.com/racket/libs/blob/master/draw-win32-x86_64-3/racket/draw/info.rkt)のcopy-foreign-libs関数の名前から
これらは何らかの時点で、ダウンロード、コピーが行われているのが推測できます。

``` racket
#lang setup/infotab

(define install-platform "win32\\x86_64")

(define copy-foreign-libs
  '("libpangowin32-1.0-0.dll"
    "zlib1.dll"
    "libjpeg-9.dll"
    "libpng16-16.dll"
    "libpixman-1-0.dll"
    "libcairo-2.dll"
    "libfreetype-6.dll"
    "libfontconfig-1.dll"
    "libexpat-1.dll"
    "libpangoft2-1.0-0.dll"
    "libpangocairo-1.0-0.dll"
    "libpango-1.0-0.dll"
    "libfribidi-0.dll"
    "libharfbuzz-0.dll"
    "libintl-9.dll"
    "libgobject-2.0-0.dll"
    "libglib-2.0-0.dll"
    "libgthread-2.0-0.dll"
    "libgmodule-2.0-0.dll"
    "libgio-2.0-0.dll"
    "libffi-6.dll"))
```

## RacketとGTK+3.0とcairoとpango

Racketはpangoテキストレンダリングライブラリーで多言語に対応して、cairoライブラリーでテキストや画像を描画します。
これらはGTK+3.0のサブプロジェクトです。また上記で多くのライブラリー依存がありますが、これはcairoとpangoが
これらに依存しているためです。

- [libcairo](https://cairographics.org/)
- [libpango](https://developer.gnome.org/pango/stable/)

## [MysterX: Legacy Support for Windows COM](https://docs.racket-lang.org/mysterx/index.html)

今は非推奨 http://download.plt-scheme.org/doc/4.2.5/html/mysterx/overview.htmlに`myssink.dll`の記述を見つけました。

## db-win32-x86_64/db/ sqlite3.dll

Racketは標準でsqlite3が使えます。

## libatk-1.0-0.dll <https://github.com/racket/libs/tree/master/gui-win32-x86_64/racket/gui>

atkライブラリは、GTKのライブラリーでATK - Accessibility Toolkit

- <https://www.gtk.org/api/2.6/atk/index.html>
