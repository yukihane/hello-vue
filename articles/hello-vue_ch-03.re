= Vue.jsの基本的な使い方

//lead{
ここでは Vue.js の基本的な使い方について簡単に書きます。

Vue.js の機能は多機能です。本稿では基本的なよく使うであろう機能を中心に解説していきます。
//}

== Vue インスタンスの作成

まずはじめに Vue インスタンスを作成することからはじまります。Vue インスタンスは以下のように生成します。

//emlist[new.js][javascript]{
new Vue({
  // オプションを記述していく
  el: '#app',
  data: {
    count: 0
  },
  methods: {
    countup: function(){
      this.count++
    }
  }
})
//}

代表的なオプションは以下のようなものがあります。

 : el
    Vueインスタンスをマウントするセレクタを登録する
 : data
    Vueで管理するデータを登録する
 : methods
    dataを操作するメソッドを登録する

methods で登録されたメソッドはのちほど解説する @<ttb>{v-on} ディレクティブで呼び出すことが可能です。

== ライフサイクル

Vue.js を使用するにあたりインスタンスのライフサイクルを抑えておくと、インスタンスの初期化処理を行う際便利です。

Vue.js はインスタンスのライフサイクルごとに呼ばれるフックを提供しています。フックはVueインスタンスを作成する際渡す引数のオブジェクトに、以下のように関数を登録して使用していきます。

//emlist[hook.js][javascript]{
new Vue({
  created: function () {
    // ここはインスタンスが作成された後に呼ばれる
    console.log('created')
  }
})
//}

フックは @<img>{vue-lifecycle} のような順番で呼ばれていきます。

//image[vue-lifecycle][Vueインスタンスのライフサイクル]{
//}

 : beforeCreate
    インスタンスが作成される前の処理
 : created
    インスタンスが作成された後の処理
 : beforeMount
    DOMにマウントされる前の処理
 : mounted
    DOMにマウントされた後の処理
 : beforeUpdate
    紐付けられたデータがアップデートされDOMが更新される前の処理
 : updated
    DOMが更新された後の処理
 : beforeDestroy
    インスタンスが削除される前の処理
 : destroyed
    インスタンスが削除された後の処理

@<img>{vue-lifecycle} のタイミングで任意のコードを実行させることが可能です。例としては beforeMount で Ajaxでデータを取得するコードを書き、得られたデータをインスタンスにセットするといった使い方をすることが可能です。使わなくてもアプリケーションの開発を行うことはできますが、要件に応じて使えるように覚えておくと良いでしょう。

== リアクティブシステム

Vue.js は data プロパティに登録したオブジェクトに属するすべてのプロパティを Vue.js 内のリアクティブシステムに取り込みます。以下のコードでは count がリアクティブになります。

//emlist[new.js][javascript]{
var newInstance = new Vue({
  el: '#app',
  // data内のプロパティはすべてリアクティブになる
  data: {
    count: 0
  }
})
//}

data プロパティの count を表示したいときは以下のように書きます。

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  count:{{ count }}
</div>
//}

HTML 内に {{}} があります。これは @<ttb>{Mustache} 構文というもので、この中に書かれたプロパティの値を展開します。今回は count の値が表示されることになります。初期値は0なため、0と表示されます。

//image[reactive_01][データの表示]{
//}

次に data の中の count を書き換えてみたいと思います。デベロッパーツールを開いて以下のコードを実行してみてください。

//emlist[increment.js][javascript]{
newInstance.$data.count++
//}

count がインクリメントされ、以下のように0から1に変わるはずです。

//image[reactive_02][インクリメントされたデータの表示]{
//}

このように count がリアクティブになり、値を変更することでビューに新しい値が反映されます。実際のアプリケーションではメソッドを介して data の中を書き換えていくことになります。

== ディレクティブ

ディレクティブは v- から始まる Vue.js で使用する特殊な属性です。主に data プロパティに登録したオブジェクトの値が変化した際、リアクティブに DOM に対して変化を加える効果があります。例としては条件分岐を行うことのできる @<ttb>{v-if} 、データの繰り返し表示に使用する @<ttb>{v-for} 、イベントリスナをアタッチするための @<ttb>{v-on} 、などがあります。

=== 条件分岐

値による条件分岐で DOM の表示非表示を操作したい時、使用できるディレクティブとして @<ttb>{v-if} と @<ttb>{v-show} が存在します。@<ttb>{v-if} と @<ttb>{v-show} の違いとしては、@<ttb>{v-if} は DOM から消してしまいますが、@<ttb>{v-show} は display 属性を none にするだけで DOM には存在するという違いがあります。また、@<ttb>{v-if} は @<ttb>{v-else-if} や @<ttb>{v-else} のように複数の条件に対応することができます。

書式はそれぞれ以下のように書きます。

//emlist[][]{
v-if="dataプロパティに登録しているオブジェクトのキー"
v-show="dataプロパティに登録しているオブジェクトのキー"
//}

v-show を試してみます。以下のようなコードを書いてみます。

//emlist[v-show.js][javascript]{
new Vue({
  el: '#app',
  data: {
    showFlg: false
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <div v-show="showFlg">
    表示されないけどDOMにいる
  </div>
</div>
//}

このコードを実行すると@<img>{v-show}のように DOM には描画されますが、display が none になり、見かけ上は表示されていないのですが DOM 上には存在するようになります。

//image[v-show][v-showではDOMに描画されるがdisplayがnoneになる]{
//}

v-if を試してみます。以下のようなコードを書いてみます。

//emlist[v-if.js][javascript]{
new Vue({
  el: '#app',
  data: {
    showFlg: false
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <div v-if="showFlg">
    表示されない
  </div>
  <div v-else>
    表示される
  </div>
</div>
//}

このコードを実行すると@<img>{v-if}のように DOM に描画されません。

//image[v-if][v-ifではDOMに描画されない]{
//}

以上のように表示に関する条件分岐は二種類の方法で実現できます。要件に応じて DOM に残す必要があるか検討し使用していくのがよいです。

=== リスト表示

リスト表示を行いたいときは @<ttb>{v-for} を使用します。@<ttb>{v-for} は他のディレクティブと違い""の中の値は特殊な文法で書いていきます。

書式は以下のように書きます

//emlist[][]{
v-for="変数名 in dataプロパティに登録しているオブジェクトのキー"
//}

リスト表示は以下のようなコードで行います。

//emlist[template.html][html]{
<ul v-for="item in items">
  <li>
    {{ item }}
  </li>
</ul>
//}

"item in items" は "item of items" と書くことも可能です。items に入れるオブジェクトは Array・Object・number・string の4種類です。それぞれのオブジェクトを使用する例を以下のように書きます。

//emlist[v-if.js][javascript]{
new Vue({
  el: '#app',
  data: {
  	array: [ "kongo", "hiei", "haruna", "kirishima" ],
    object: {
      "hoge": "hogehoge",
      "fuga": "fugafuga"
    },
    number: 10,
    string: "Lorem"
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <h2>
    array
  </h2>
  <ul v-for="(item, index) in array">
    <li>
      {{ item }} - {{ index }}
    </li>
  </ul>
  <h2>
    Object
  </h2>
  <ul v-for="(val, key, index) in object">
    <li>
      {{ val }} - {{ key }} - {{ index }}
    </li>
  </ul>
  <h2>
    number
  </h2>
  <ul v-for="(num, index) in number">
    <li>
      {{ num }} - {{ index }}
    </li>
  </ul>
  <h2>
    string
  </h2>
  <ul v-for="(char, index) in string">
    <li>
      {{ char }} - {{ index }}
    </li>
  </ul>
</div>
//}

表示結果を以下のようになります。

//image[v-for_01][Array]{
//}

//image[v-for_02][Object]{
//}

//image[v-for_03][number]{
//}

//image[v-for_04][string]{
//}

このように様々なオブジェクトに対してリスト表示を行うことが可能です。よく使用するのは主に配列に対するリスト表示だと思われます。配列に対して追加や削除を行うとそれに応じてリストは再レンダリングされます。

配列に対して行うことのできる操作は以下です。

 : push()
    配列の最後に要素の追加
 : pop()
    配列の最後を取得
 : shift()
    配列の最初の要素を取得
 : unshift()
    配列の最初に１個以上の要素を追加
 : splice()
    複数の要素を追加・削除
 : sort()
    配列を並び替える
 : reverse()
    配列を逆転する

Vue.js の data プロパティの配下は Vue.js によって変更メソッドがラップされているため、先程示した関数などで変更を行うとリアクティブに DOM が書き換えられます。通常の配列の操作ではインデックスで直接要素を指定し上書きすることができますが、その操作はでは Vue.js が変更を検出できないため、リアクティブに DOM が書き換わることがありません。配列に操作を加える際は上記のメソッドを介して行いましょう。

リスト表示の部分は Vue.js の事情により複雑です。ガイド@<fn>{list-guide}を参照して開発を行いましょう。

=== イベントリスナ

DOM に対してクリックやホバーを検出したい場合、@<ttb>{v-on} を使うことでイベント発火時に任意のメソッドを実行することが可能です。書式としては以下のようにディレクティブを書くことで実現します。

//emlist[][]{
v-on:イベント名="行いたい処理"
//省略記法
@イベント名="行いたい処理"
//}

簡単な例では以下のように書くと DOM をクリックした際ダイアログを出すことができます。

//emlist[template.html][html]{
<div v-on:click="alert('hoge')">alert</div>
//}

"" の中に JavaScript コードを書くことができます。ですがこの例のように "" の中に書いていくスタイルでは複雑なコードを書きたい場合現実的ではありません。

その時は Vue インスタンスを作成する際 methods プロパティに登録したメソッドの名前を記入することで、その処理を実行することで対応します。簡単な例を以下に書きます。

//emlist[v-on.js][javascript]{
new Vue({
  el: '#app',
  methods: {
  	showAlert: function () {
    	alert('hoge')
    }
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <div v-on:click="showAlert">
    alert
  </div>
</div>
//}

このように書くと methods 内の showAlert メソッドが実行されます。動作は先ほどのコード例と同じ動作をします。

また methods 内のメソッドで data プロパティに登録されているオブジェクトは this を介して参照することができるので、参照したデータの操作を行い、DOM をリアクティブに書き換え、動的なアプリケーションの開発を行うことができます。

以下のコードは data プロパティに登録されているオブジェクトを更新して表示する例です。

//emlist[increment.js][javascript]{
new Vue({
  el: '#app',
  data: {
    count: 0
  },
  methods: {
  	increment: function () {
    	this.count += 1
    }
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <div v-on:click="increment">
    increment
  </div>
  {{ count }}
</div>
//}

increment と表示された部分をクリックすることで、data プロパティ内の count が更新され、数値がインクリメントされていくのがわかると思います。

//image[v-on][incrementをクリックすると数値が更新されていく]{
//}

=== フォーム

form を実装しようとする時は @<ttb>{v-model} が役に立ちます。@<ttb>{v-model} は form 内の input と textarea 要素で双方向データバインディングを実現します。

以下 @<ttb>{v-model} を用いた双方向データバインでキングのコード例です。

==== テキスト

通常のテキストの双方向バインディングを試してみるため、以下のコードを書いてみます。

//emlist[v-model_01.js][javascript]{
new Vue({
  el: '#app',
  data: {
    text: ""
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <input v-model="text">
  <p>
    {{ text }}
  </p>
</div>
//}

テキストの入力を行ったら @<img>{v-model_01} のようにすぐ p タグ内に反映されることがわかると思います。

//image[v-model_01][テキスト入力]{
//}

==== 複数行テキスト

通常の textarea を用いた双方向バインディングを試してみます。

//emlist[v-model_02.js][javascript]{
new Vue({
  el: '#app',
  data: {
    text: ""
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <textarea v-model="text"></textarea>
  <p>
    {{ text }}
  </p>
</div>
//}

こちらもテキストの入力を行ったら @<img>{v-model_02} のようにすぐ p タグ内に反映されることがわかると思います。気をつけないといけないことは、textarea 内で改行を行ったとしても、それは改行文字として認識されてしまうため、p タグ内では何も表示されない空の文字として表示されてしまう点です。これに関しては改行を HTML 上に表示する際 br タグなどにする処理を入れる必要があります。

//image[v-model_02][複数行テキスト入力]{
//}

==== チェックボックス

チェックボックスの双方向バインディングを試してみます。

チェックボックスは単体と複数選択の場合では使用方が若干異なります。単体での使用の場合、data プロパティの値は boolean 型になり、複数での使用の場合は配列になります。

単体での使用例を書いてみます。

//emlist[v-model_03.js][javascript]{
new Vue({
  el: '#app',
  data: {
    checked: false
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <input type="checkbox" id="checkbox" v-model="checked">
  <label for="checkbox">{{ checked }}</label>
</div>
//}

チェックボックスをチェックするとの @<img>{v-model_03} ように true になり、チェックを外すと false になります。

//image[v-model_03][チェックボックス単体使用]{
//}

複数での使用例を書いてみます。

//emlist[v-model_04.js][javascript]{
new Vue({
  el: '#app',
  data: {
    checkedNames: []
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <input type="checkbox" id="kongou" value="Kongou" v-model="checkedNames">
  <label for="kongou">Kongou</label>
  <input type="checkbox" id="hiei" value="Hiei" v-model="checkedNames">
  <label for="hiei">Hiei</label>
  <input type="checkbox" id="haruna" value="Haruna" v-model="checkedNames">
  <label for="haruna">Haruna</label>
  <input type="checkbox" id="kirishima" value="Kirishima" v-model="checkedNames">
  <label for="kirishima">Kirishima</label>
  <br>
  <span>{{ checkedNames }}</span>
</div>
//}

チェックボックスをチェックすると @<img>{v-model_04} ようにチェックした項目名が表示されます。

//image[v-model_04][チェックボックス複数使用]{
//}

単体での使用はチェックしたか否かの情報を保持し、複数での使用は何をチェックしたかの情報を保持します。要件に応じた使い分けをしていくと良いでしょう。

==== ラジオボタン

ラジオボタンの双方向バインディングを試してみます。

//emlist[v-model_05.js][javascript]{
new Vue({
  el: '#app',
  data: {
    modulation: ""
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <input type="radio" id="fm" value="FM" v-model="modulation">
  <label for="fm">FM</label>
  <br>
  <input type="radio" id="am" value="AM" v-model="modulation">
  <label for="am">AM</label>
  <br>
  <span>Modulation: {{ modulation }}</span>
</div>
//}

チェックした値が modulation に保持され、切り替わることが @<img>{v-model_05} でわかります。

//image[v-model_05][チェックボックス複数使用]{
//}

==== セレクト

select の双方向バインディングを試してみます。

select もチェックボックスと同じように単体選択と複数選択で使用法が異なります。単体選択の場合は string、複数選択の場合は配列で選択された値を保持します。

単体選択の場合の例を書きます。

//emlist[v-model_06.js][javascript]{
new Vue({
  el: '#app',
  data: {
    hisyo: ""
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <select v-model="hisyo">
    <option disabled value="">秘書艦を選んでください</option>
    <option>金剛</option>
    <option>比叡</option>
    <option>榛名</option>
    <option>霧島</option>
  </select>
  <span>秘書艦: {{ hisyo }}</span>
</div>
//}

選択された値が hisyo に保持され表示が変わることが @<img>{v-model_06} でわかります。

//image[v-model_06][セレクトの単体選択]{
//}

複数選択の場合の例を書きます。

//emlist[v-model_06.js][javascript]{
new Vue({
  el: '#app',
  data: {
    kantai: []
  }
})
//}

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<div id="app">
  <select v-model="kantai" multiple>
    <option disabled value="">艦隊を組むための艦娘を選んでください</option>
    <option>金剛</option>
    <option>比叡</option>
    <option>榛名</option>
    <option>霧島</option>
  </select>
  <span>艦隊: {{ kantai }}</span>
</div>
//}

選択された値が kantai に保持され、選択された項目が表示されることが @<img>{v-model_07} でわかります。

//image[v-model_07][セレクトの複数選択]{
//}

== コンポーネント

Vue.js はコンポーネントシステムを備えています。機能ごとのコンポーネントを作成し、それを組み合わせることによって画面を構成していく事ができます。

=== コンポーネントの書式

シンプルに表示だけを行うコンポーネントは以下のように書きます。

//emlist[v-component_01.js][javascript]{
Vue.component('item', {
  template: '<div>item</div>'
})
//}

このコンポーネントを利用する際は、Vue.js によってバインドされているDOMに以下のように書きます。

//emlist[template.html][html]{
<h1>Hello Vue !!</h1>
<!-- #app にマウントされているとします -->
<div id="app">
  <item></item>
</div>
//}

Web Components のカスタム要素のように利用することが可能です。

=== props

== まとめ

Vue.js の基本的な使い方について書いていきました。他にもコンポーネント@<fn>{component-guide}や、算出プロパティ@<fn>{compute-guide}、トランジション@<fn>{transition-guide}などがありますが、より高度な使用方になるのでここでは触れません。更に先に進んでみたくなった場合はガイドを参照して開発を行ってみてください。

//footnote[list-guide][公式ガイド リストレンダリング：https://jp.vuejs.org/v2/guide/list.html]
//footnote[component-guide][公式ガイド コンポーネント：https://jp.vuejs.org/v2/guide/components.html]
//footnote[compute-guide][公式ガイド 算出プロパティとウォッチャ：https://jp.vuejs.org/v2/guide/computed.html]
//footnote[transition-guide][公式ガイド Enter/Leave とトランジション一覧：https://jp.vuejs.org/v2/guide/transitions.html]
