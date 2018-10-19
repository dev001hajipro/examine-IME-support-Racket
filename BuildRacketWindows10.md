# Windows10でRacketをビルド

## 環境
* Windows10 64bit
* Build Tools for Visual Studio

## Racket本体とmain-distributionについて

Racket本体のプロジェクト(<https://github.com/racket/racket>)は、コンパイラーやランタイムのプロジェクトです。

標準ライブラリーや標準機能は、
[main-distribution](https://pkgd.racket-lang.org/pkgn/search?q=main-distribution)として各自プロジェクト化(=パッケージ化)されています。
単純な例として、数学ライブラリーのmathや、通信ライブラリーのnetがmain-distributionにあります。IDEのDrRacketも同じです。

Racket本体をcloneしてビルドすると、ビルドの最後でmain-distributionがダウンロードされ、rktファイルであればビルドされます。そのため数時間かかります。

## Racket本体のビルドとmain-distributionのビルド方法の参考資料

- [Tutorial: Contributing to Racket](http://blog.racket-lang.org/2017/09/tutorial-contributing-to-racket.html) 

## ビルド作業

この例では`C:\workspace_racket`で作業します。

```powershell
> git clone https://github.com/racket/racket.git
> nmake win32-in-place
```

README.mdやINSTALL.txtなどを見るとかなり長く書かれていますが、`namke win32-in-place`を実行するだけです。
内部でracket/src/worksp/build.batを実行します。

### SSLでエラーが発生

ライブラリーが不足しているので <https://github.com/racket/libs> から racket-win32-x86_64-3(最新)を入手して、`racket/racket/lib`に配置。

```
racket/racket/lib
    libeay32.dll
    libiconv-2.dll
    longdouble.dll
    ssleay32.dll
```

#### Makefile修正

racket/Makefileのwin32-baseタスクの先頭行をコメントアウトします。このタスクはnmake時に上記ライブラリーを削除します。

```Makefile
win32-base:
    #$(MAKE) win32-remove-setup-dlls <<< この行をコメントアウトした
    IF NOT EXIST build\config cmd /c mkdir build\config
    cmd /c echo #hash((links-search-files . ())) > build\config\config.rktd
    cmd /c racket\src\worksp\build-at racket\src\worksp ..\..\..\build\config $(JOB_OPTIONS) $(PLT_SETUP_OPTIONS)
```

#### 何故コメントアウトするか

racketをビルド後、racket自身がracoコマンドでmain-distribution(ランタイムに必要な各種標準ライブラリー)をネットワークから取得します。
この時racketの今ビルドされたライブラリーでgithubにHTTPS接続しますが、上記ライブラリーがないとtls1.2が使えません。
現在githubは、tls1.2より前のバージョンのHTTPS接続禁止しているため、エラーが発生します。

## 環境変数pathの変更

公式のRacketをインストールしている場合やそちらにパスを通している場合、現在ビルドしたracketやracoコマンドを
使うためにパスを`C:\workspace_racket\racket\racket;`などに変更します。

## main-distributionのDrracketのclone

racket本体をビルドしたときに、main-distributionの１つとしてDrRacketもダウンロードしてビルドされます。

開発者がDrRacketのソースコードを修正して実行するためには、DrRacketを別途githubからcloneしてこちらを使うようにracoコマンドで関連付けます。

通常の`git clone <url>`ではなく、`raco pkg install --clone`を使うと、githubからcloneと関連付けを行ってくれます。

**`rack pkg update --clone`を使うはずですが、updateを試してその後installを行いました。**

```powershell
mkdir extra-pkgs
cd extra-pkgs
raco pkg install --clone https://github.com/racket/drracket
raco pkg show
```

`rack pkg show`を実行すると、Sourceカラムに、clone...=drracketとなり、main-distributionから独立してソースコードを参照しているのが確認できます。

```powershell
> raco pkg show
Installation-wide:
 Package                 Checksum           Source
 drracket                d8dab5865c3560...  clone...=drracket
 main-distribution       a94ec086a48e7d...  catalog...ibution
 main-distribution-test  c1a62206635d76...  catalog...on-test
 [238 auto-installed packages not shown]
User-specific for installation "development":
 [none]
```

上記でmain-distributionのDrRacketを`raco pkg update`でビルドしましたが、他のmain-distributionもおなじようにできます。

## DrRacketのソースコードを修正してビルドする方法

コードを修正したら、`raco setup drracket`でビルドしてexeまで作成します。

```
 raco setup drracket
```
 
### Native LibraryとDLL

Windows 64bit版のnative libraryは、https://github.com/racket/libsでpre-buildで公開されています。
Racketは、最終的にはこれらnative libraryを呼び出して描画などを行います。

#### draw-win32-x86_64

https://github.com/racket/libs/tree/master/draw-win32-x86_64
https://github.com/racket/libs/blob/master/draw-win32-x86_64/racket/draw/info.rkt

```
(define copy-foreign-libs (quote ("libjpeg-8.dll" "libcairo-2.dll" "libpango-1.0-0.dll" "libexpat-1.dll" "libpng14-14.dll" "zlib1.dll" "libfreetype-6.dll" "libintl-8.dll" "libfontconfig-1.dll" "libglib-2.0-0.dll" "libgobject-2.0-0.dll" "libgmodule-2.0-0.dll" "libgthread-2.0-0.dll" "libpangocairo-1.0-0.dll" "libpangowin32-1.0-0.dll" "libpangoft2-1.0-0.dll")))
```

- libcairo:https://cairographics.org/
- libpango
  - https://www.pango.org/
  - https://developer.gnome.org/pango/stable/
- libpangocairo
- libpangowin32

#### myssink.dllとは?
- https://docs.racket-lang.org/mysterx/index.html
- http://download.plt-scheme.org/doc/4.2.5/html/mysterx/overview.html

#### db-win32-x86_64/db/
sqlite3.dll

#### gui
atkライブラリは、GTKのライブラリーでATK - Accessibility Toolkit
https://github.com/racket/libs/tree/master/gui-win32-x86_64/racket/gui

libatk-1.0-0.dll

https://www.gtk.org/api/2.6/atk/index.html


## GTK+のインストールでpangoも依存でインストール

https://www.gtk.org/download/windows.php

### GTK+インストール

MSYS32でインストールすればWindowsでも使えます。
https://www.gtk.org/download/windows.php

GTK+と各種インストールをしたらpangocairoもインストールされました。

```bash
$ pkg-config --cflags pangocairo
-mms-bitfields -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/fribidi -IC:/msys64/mingw64/include/cairo -IC:/msys64/mingw64/include -IC:/msys64/mingw64/lib/libffi-3.2.1/include -IC:/msys64/mingw64/include/pixman-1 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/freetype2 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/libpng16 -IC:/msys64/mingw64/include

```

### text% クラスは、gui-libで実装されている

https://github.com/racket/gui/tree/master/gui-lib
https://pkgs.racket-lang.org/package/gui-lib

main-distributionなので、DrRacketと同様にracoからcloneできるはず。

### 参考資料

- https://stackoverflow.com/questions/41492532/undo-a-raco-pkg-update-clone-or-raco-pkg-install-clone
- [Tutorial: Creating a Package](http://blog.racket-lang.org/2017/10/tutorial-creating-a-package.html)
- [Tutorial: Contributing to Racket](http://blog.racket-lang.org/2017/09/tutorial-contributing-to-racket.html)
