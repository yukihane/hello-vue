= Vue.jsことはじめ

//lead{
Vue.js とは一体どのようなフレームワークなのでしょうか。この章では Vue.js そのものについてや、エコシステムやコミュニティについて書いていきます。
//}

== Vue.js とは

Vue.js とはインタラクティブ性のあるユーザインタフェースを構築するための JavaScript のフレームワークです。

Vue.js は Evan You（https://github.com/yyx990803）さんの個人プロジェクトとして2013年に開発が開始され、2015年10月に 1.0、2016年10月に 2.0 がリリースされ、現在（2017年10月）最新のバージョンは 2.5.2 となっています。Evan さんは現在フルタイムで Vue.js を開発しており、開発の支援も様々な企業や個人スポンサーから受けているため、ほぼ万全の体制での開発が出来ている状態と言えます。

Vue.js の機能的な特徴としては MVVM（Model-View-ViewModel）のソフトウェアアーキテクチャパターンの影響を受けていることです。データと DOM がフレームワークによって紐付けられることにより、データに変更があればリアクティブに DOM の描画を変更できるという特徴があります。

またコンポーネント指向の開発もサポートされており、機能ごとにコンポーネントを分解し保守性高いコードを書くことが可能です。

== Progressive Framework

Vue.js の特徴として、Progressive Framework という概念にもとづいて開発されているということがあります。

Progressive Framework とは Evan さんが提唱した概念で、アプリケーションの要求に応じて使い方を変えていくことのできるフレームワークのことを指すようです@<fn>{progressive-framework}。

たとえば、まずはじめにリアクティブな仕組みを使ってフォームを作りデータを送る要求のみ満たすために Vue.js を使うとします。これだけならば単に script タグで Vue.js を読み込み、HTML に直接ディレクティブ（Vue.js の為にタグに追加する属性）を書くだけで十分です。

その次に form を使い回したいという要求が出てきたとき、Vue.js のコンポーネントの機能を使用することで満たすことが出来ます。素のままのコードでコンポーネントを使用するとコードが見辛くなる事があると思います。そのときはコンポーネントごとに .vue ファイルに分割し、各種バンドルツールに応じた Vue.js の plugin を利用することでファイルの分割とビルドの仕組みを構築することが出来ます。

SPA などのより「アプリケーション」らしいものにしていきたいと考えたとき、vue-router や vuex などの plugin を使用し要求を満たすことが可能です。サーバーサイドレンダリングが必要だと判断したら、Nuxt.js を使うことができます。

以上のように Vue.js とそれを取り巻く plugin などのエコシステムは、簡単な Web ページから Web アプリケーションまで様々な要求に対応することが可能です。plugin は主要なものは Evan さんによりは公式なサポートが行われているため、連携も自然に出来るようになっており安心感をもって導入ですることができます。

== コミュニティ

コミュニティ活動は各国で活発に行われており、特に2017年6月にポーランドで行われた VueConf@<fn>{vue-conf} は Vue.js の開発コアメンバーが勢揃いし大変な盛り上がりを見せました。

日本のコミュニティとしては Vue.js 日本ユーザーグループ@<fn>{vue-japan}が存在し、Slack を通じて活発な情報交換が行われています。ドキュメントの和訳などはここで参加者を募っており、 vue-loader や サーバサイドレンダリングガイド、Nuxt.js などのプロジェクトのドキュメントの和訳がここで提起されリリースに至っています。

Vue.js を用いていてもし不明な点があれば公式フォーラム@<fn>{vue-forum}を利用することで解答を得られます。日本語のカテゴリでは日本語で質問することが可能です。

== ガイド

Vue.js の特徴の一つとして豊富な日本語ガイドがあげられます。Vue.js に関連するものとしては以下のものがあります。

 : 公式ガイド
    https://jp.vuejs.org/v2/guide/
 : Vue.js サーバーサイドレンダリングガイド
    https://ssr.vuejs.org/ja/
 : スタイルガイド（翻訳途中）
    https://jp.vuejs.org/v2/style-guide/
 : vue-loderのドキュメント
    https://ja.nuxtjs.org/guide/
 : vue-routerのドキュメント
    https://router.vuejs.org/ja/
 : Vuexのドキュメント
    https://vuex.vuejs.org/ja/
 : Nuxt.jsのガイド
    https://ja.nuxtjs.org/guide/

ドキュメントは非常に良く作られているため、問題が起きた際はドキュメントに立ち返ることで解決作がわかることが多いです。初心者にわかりやすいドキュメントを提供しているあたりも Vue.js の文化の特徴と言えると思います。

またこれらのガイドは github で管理されており、誤字脱字や誤訳などがあれば気軽に pull request を送ることで修正をすることが可能です。

== 派生プロジェクト

派生プロジェクトとして Weex@<fn>{weex} というネイティブなモバイルアプリケーションを作成するためのフレームワークも存在します。React で言うところの ReactNative に相当するもので、 .vue ファイルを用いて開発していくのが特徴です。

以前は alibaba グループによって開発が行われていたようですが、今は apache foundation に移管されて開発が続けられています。まだ ReactNativeほど洗練されていませんが、.vue ファイルがそのままネイティブアプリケーションの画面開発に使えるのは、Vue.js のアプリケーション開発者にとってはとても魅力的だといえます。

ユニバーサルなアプリケーションを作成するためのフレームワークである、 Nuxt.js も存在します。これも React で言うところの Next.js に相当するものです。vue-router や vuex も組み込まれており、動的なWebサイトを簡単に作ることが可能です。

Nuxt.js はサーバーサイドレンダリングをする Vue.js のアプリケーションを楽にするため、必要な設定はすべて組み込まれています。Webpack や babel の設定を初めは書く必要が無いので素早くアプリケーションの開発を行うことができます。

== まとめ

以上 Vue.js の簡単な紹介を行いました。Vue.js を取り巻くコミュニティやエコシステムについて、派生プロジェクトについて知っていただけたと思います。

Vue.js はそのドキュメントの充実度から、学びやすく導入しやすいフレームワークだと言われています。ガイドの節で紹介したWebページを読むだけで開発をすすめることが可能です。

次の章から具体的な使い方に入っていこうと思います。

===[column] Vue.jsのバージョンごとのコードネーム

Vue.js の面白い要素の一つとして、マイナーバージョンごとに映画や漫画、アニメのタイトルが使われていることです。

順番通りなら次は M になります。次のバージョンのコードネームを推測するのも Vue.js を愉しむ一つの要素となっています。

//table{
バージョン	コードネーム
-------------------------------------------------------------
v2.5.0	Level E
v2.4.0	Kill la Kill
v2.3.0	JoJo's Bizarre Adventure
v2.2.0	Initial D
v2.1.0	Hunter X Hunter
v2.0.0	Ghost in the Shell
v1.0.0	Evangelion
v0.12.0	Dragon Ball
v0.11.0	Cowboy Bebop
v0.9.0	Animatrix
//}

===[/column]

//footnote[progressive-framework][Progressive framework：https://docs.google.com/presentation/d/1WnYsxRMiNEArT3xz7xXHdKeH1C-jT92VxmptghJb5Es/edit?usp=sharing]
//footnote[vue-conf][VueConf：https://conf.vuejs.org/]
//footnote[vue-japan][Vue.js 日本ユーザグループ：https://github.com/vuejs-jp/home]
//footnote[vue-forum][Vue.js 公式フォーラム：https://forum.vuejs.org/]
//footnote[weex][Weex：https://weex.incubator.apache.org/]
