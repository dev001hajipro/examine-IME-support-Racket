# text%パッケージのビルド

ここでは、guiパッケージにWin32APIが見つかったことと、guiパッケージのclone方法を記述します。
またcloneする際に、urlではなくracketのパッケージ名でする方法説明します。

## 参考資料 

- [Developing Packages with Git](https://docs.racket-lang.org/pkg/git-workflow.html)

## CreateWindowExWなどWin32APIの記述が、.rktから発見！

闇雲に見ていると、<https://github.com/racket/gui/blob/master/gui-lib/mred/private/editor.rkt>に
editor<%>インタフェースとtext%オブジェクトを外部に公開しているeditor.rktファイルを見つけました。

```
(provide editor<%>
         text%
         pasteboard%
         editor-snip%
         current-text-keymap-initializer
         append-editor-operation-menu-items
         append-editor-font-menu-items)

(define editor<%>
```

また、 requireに`(prefix-in wx: "wxme/editor.rkt")`とありこれも気になります。
```
(require racket/class
         racket/list
         racket/file
         racket/path
         (for-syntax racket/base)
         (prefix-in wx: "kernel.rkt")
         (prefix-in wx: racket/snip/private/style)
         (prefix-in wx: racket/snip/private/snip)
         (prefix-in wx: "wxme/keymap.rkt")
         (prefix-in wx: "wxme/editor.rkt")
```

また、<https://github.com/racket/gui/tree/master/gui-lib/mred/private/wx/win32>では、CreateWindowExWやSendMessageWが.rktファイルで
記述され、このパッケージでdllとRacketが繋がっているのが分かってきました。

DrRacketと同様にローカルにcloneします。


## `rack pkg install git://github.com/racket/gui/?path=gui`で失敗

gui-libの親は[gui](https://pkgs.racket-lang.org/package/gui)パッケージなので、これを`raco pkg install`します。

`rack pkg install git://github.com/racket/gui/?path=gui`を実行したら、Windows10ではディレクトリーが作成されず、
また、guiパッケージがconflictしているとエラーが発生しました。その後、コマンドを調べて以下の手順を行いました。

### `update <dir> <pkg-name>`コマンドの意味と、パッケージ名でcloneする方法

```bash
raco pkg update <dir> <pkg-name>
```

DrRacket,math,net,guiパッケージなどは、Racket本体をビルドしたときにmain-distributionとして標準で依存関係となります。

githubからguiパッケージのソースコードをcloneする場合は、標準でインストール済み(依存関係済み)の状態から、
新たにcloneするソースコードに向きを変える必要があります。そのため、`raco pkg install`ではなく
`raco pkg update`を使います。

また、Windows10の場合、clone元をURLで指定すると、`https:`ディレクトリーを作成しようとしてエラーが発生します。

```bash
raco pkg update --clone git://github.com/racket/gui/?path=gui
```

指定のディレクトリーにcloneするためには`--clone`の引数に`<dir>`を追加します。
以下のように`gui`を書くとguiディレクトリーを作りそこにcloneします。

```bash
raco pkg update --clone gui git://github.com/racket/gui/?path=gui
```

これでもWindow10ではうまくいきません。代案として、`<dir> <pkg-name>`でうまくいきます。
この<pkg-name>は、[https://pkgs.racket-lang.org/package/gui](https://pkgs.racket-lang.org/package/gui)に登録されている
名称です。

よって、clone先のディレクトリーをguiにして、pkg-nameがguiのものをアップデートするという
コマンドを実行します。

``` bash
raco pkg update --clone gui gui
```

これで、guiパッケージのソースコードを修正する準備が整いました。

``` powershell
> raco pkg show
Installation-wide:
 Package                 Checksum           Source
 drracket                d8dab5865c3560...  clone...=drracket
 gui                     416d51d4dc834c...  clone...?path=gui
 main-distribution       a94ec086a48e7d...  catalog...ibution
 main-distribution-test  c1a62206635d76...  catalog...on-test
 [237 auto-installed packages not shown]
User-specific for installation "development":
 [none]
 ```
