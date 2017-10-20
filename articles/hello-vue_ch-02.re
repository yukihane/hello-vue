= Vue.jsのはじめかた

//lead{
早速 Vue.js を使い始めたいと考えたとき、どのようにはじめれば良いでしょうか？

本章では Vue.js の始め方について書いていきます。
//}

== CDNを使う

簡単に Vue.js を試すには CDN を利用するのが良いです。CDN は unpkg@<fn>{unpkg}  を利用すると script タグで以下のように読み込みます。

//emlist[][html]{
<script src="https://unpkg.com/vue"></script>
//}

はじめはこのように簡単に読み込んで Vue.js の機能を試すのが楽で良いです。script タグで読み込むだけでは .vue ファイルによる単一ファイルコンポーネントの機能を使うことは出来ませんが、その分ビルドのためのスクリプトについて考える必要がないので Vue.js 自身の学習に集中することが出来るので、初めのうちはこちらをお薦めします。

== npm を利用して環境を構築する

ある程度慣れてきたら npm もしくは yarn を用いて環境を構築するのがよいです。npm や yarn などのパッケージ管理ツールを用いて Vue.js の開発環境を構築するには一般的にバンドルツールを用いて行うのが最近の主流となっています。

バンドルツールは Webpack や Browserify などを使うことが可能です。それぞれのバンドルツールごとに Webpack は vue-loader、Browserify は vueify といったプラグインがあります。これらのプラグインは Vue.js の強力な機能である単一ファイルコンポーネントを利用するときに必要になります。

単一ファイルコンポーネントを用いると template script style の三つがセットになったコンポーネント単位のファイルを作ることが可能になります。マークアップと動作がセットになったファイルは、複数のページで共通して使用する部品などを作る際にとても便利です。

このように npm などを利用して開発環境を構築することで、Vue.js の強力な機能を使い開発を行うことが出来ます。

== vue-cliを利用して環境を構築する

npm や yarn を使って環境構築をする際、ビルドスクリプトやビルドのための設定を作らなくてはならないため、スクリプトの作成に追われ本質的なアプリケーション開発になかなか入れないことにフラストレーションを感じるかも知れません。そういう場合は vue-cli の使用を検討すると良いでしょう。

vue-cli は Vue.js を使ったプロジェクトの scaffolding をするコマンドラインツールです。引数にテンプレート名を与えることでそのテンプレートを使用してプロジェクトのひな形を作ることが出来ます。

コマンドは以下のようにして実行することにより、プロジェクトを作成できます。

//cmd{
$ @<b>{vue init テンプレート名 プロジェクト名}
//}

プロジェクト名で指定した名前のディレクトリが作成され、テンプレート名で指定されたテンプレートでプロジェクトが作成されます。

オフィシャルなテンプレートは@<table>{vue-cli-template}があります。

//table[vue-cli-template][vue-cliのオフィシャルテンプレート]{
テンプレート名	詳細
-------------------------------------------------------------
webpack	フルセットのWebpackテンプレート。ホットリロード、lint、テストなどの設定がフルに入っている。
webpack-simple	必要最小限のWebpackテンプレート。最低限ビルドが出来る設定が入っている。
browserify	フルセットのBrowserifyテンプレート。ホットリロード、lint、テストなどの設定がフルに入っている。
browserify-simple	必要最小限のBrowserifyテンプレート。最低限ビルドが出来る設定が入っている。
pwa	PWAのアプリケーションを作るためのテンプレート。webpackをベースにしている。
simple	scriptファイルでCDNの Vue.js を読み込むHTMLファイルを作るだけのテンプレート。
//}

webpack などのフルセットのテンプレートを利用するのはある程度慣れてからのほうが良いです。初心者であれば webpack-simple などで最小限のビルドの設定を使い拡張していくのが良いでしょう。ホットリロードやlint等についてある程度詳しいのであればフルセットを利用し開発をはじめると本質的なアプリケーション開発にすぐに入ることが出来るのでお薦めです。

== Ruby on Railsで使う

もし Ruby on Rails を使って Webアプリケーションを構築するのであれば、webpacker を利用するのが Rails のレールに乗った開発が出来るのでお薦めです。ここではRailsのv5.1.4、webpackerはv3.0.2を使用します。

まず webpacker を使用するために Gemfile に追記し @<code>{bundle install} を実行しインストールします。

//list[webpacker-gem][Gemfile]{
gem 'webpacker', '~> 3.0'
//}

その後 webpacker の設定を @<code>{rails} コマンドでインストールします。インストールした後 webpacker の設定等を rake タスクでインストールします。

//cmd{
$ @<b>{bundle install}
$ @<b>{bundle exec rails webpacker:install}
//}

このコマンドを実行すると以下のファイルが追加されます。

 : .babelrc
    babelの設定。
 : .postcssrc.yml
    postcssの設定
 : app/javascript/packs/application.js
    railsのhelperのjavascript_pack_tagで読み込むJavaScriptファイル
 : bin/webpack
    webpackのwrapper
 : bin/webpack-dev-server
    webpack-dev-serverのwrapper
 : config/webpacker.yml
    webpackの設定が書かれたyml
 : config/webpack/development.js
    development環境用のwebpackの設定を追記するJavaScriptファイル
 : config/webpack/environments.js
    node_modulesのwebpackerで設定を読み込むJavaScriptファイル
 : config/webpack/productions.js
    production環境用のwebpackの設定を追記するJavaScriptファイル

webpacker の設定等 rake タスクで追加した後、Vue.js のインストールを rake タスクで行います。

//cmd{
$ @<b>{bundle exec rails webpacker:install:vue}
//}

このコマンドを実行すると以下のファイルが追加されます。

 : app/javascript/app.vue
    Hello Vue! と表示するだけのコンポーネント
 : app/javascript/pacls/hello_vue.js
    app.vue を使用するJavaScriptファイル

ほかにも package.json に vue,vue-loader,vue-template-compiler が追加され yarn でインストールされます。

hello_vue.js を javascript_pack_tag で読み込むと Hello Vue! と表示されます。

最低限の設定しか施されていないので、templateにpugを使いたい、styleにscssを使いたい等があれば自身でインストールする必要があります。

== まとめ

このように様々な方法で Vue.js をはじめることが可能です。自身のプロジェクトにあった方法でインストールを行い、開発を進めていきましょう。

//footnote[unpkg][UNPKG：https://unpkg.com/]
