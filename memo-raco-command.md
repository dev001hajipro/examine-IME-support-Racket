# racoコマンドのオプションを調べた時のメモ

はじめてracketをビルドしたときに、エラーが発生したのでその時にracoコマンドのオプションを調べた時のメモです。

## エラーが発生した時のログは以下のように複雑でした。

```
racket\racket -G racket/etc -X racket/collects -N raco -l- raco pkg install --help
```

## 分解

`-l- raco`前までは、racket.exeのオプションです。

- racket\racket
  racket\Rakect.exeがあり、これを多くのオプションと共に実行します。

- -G racket/etc
  コンフィグの指定

- -X racket/collects
  メインのcollectsディレクトリー指定
  
- -N raco
  (find-system-path 'run-file)をracketからracoに変更
  
- -l- raco
  `-l -- raco`と同じ意味で、(require (lib "raco"))と同じ、此処までの各種パスの設定で、raco.exeをこれで実行
  
`raco pkg install --help`は、通常のracoコマンドのオプションです。

```
 raco pkg install
		--no-setup この後 raco setupを実行しない
		--pkgs 指定のみインストールを行う
		--skip-installed　インストール済みなら<pkg-source>をスキップ
		--scope installation OSのすべてのユーザー向けインストール
		--deps search-auto 問い合わせずに依存関係を探す
		main-distribution main-distribution-test
 ```
