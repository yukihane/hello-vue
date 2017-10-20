= ToDoリストを作る

//lead{
ここでは実際に Vue.js を使ってToDoリストを作っていきます。

簡単なアプリケーションを作ることで Vue.js の理解を深めていければと思います。
//}

== フォームを作る

まずは入力フォームを作成します。input タグへの入力には @<ttb>{v-model} ディレクティブを使って双方向データバインディングを用いてデータを data プロパティに登録したオブジェクトに保持します。

//emlist[todo.js][javascript]{
new Vue({
  el: '#app',
  data: {
    todo: ""
  }
})
//}

//emlist[template.html][html]{
<div id="app">
  <form>
    <input v-model="todo">
    <input type="submit" val="追加">
  </form>
  <!-- 確認用 -->
  {{ todo }}
</div>
//}

input タグに入力してデータが表示されることを @<img>{form_01} のように確認できるはずです。

//image[form_01][formを作った状態]{
//}

== リストの作成

表示するリストを定義します。data プロパティに list を追加します。listを @<ttb>{v-for} ディレクティブを使って表示していきます。

//emlist[todo.js][javascript]{
new Vue({
  el: '#app',
  data: {
    todo: "",
    list: ["hoge", "fuga"] //確認用にデータを入れる
  }
})
//}

//emlist[template.html][html]{
<div id="app">
  <form>
    <input v-model="todo">
    <input type="submit" val="追加">
  </form>
  <ul v-for="item in list">
    <li>
      {{item}}
    </li>
  </ul>
</div>
//}

確認用のデータが @<img>{form_02} のように表示されることを確認できると思います。

//image[form_02][リストを追加]{
//}

この状態では特に list に追加する処理を書いていないため、form はまだ機能していません。

== listに追加できるようにする

list に追加するために現在の todo の内容を list に追加する処理を書かなくてはいけません。form の送信イベントに連動して list に追加されていく処理を書いていきます。送信イベントで発火する関数を @<ttb>{v-on} ディレクティブで実行されるように書いていきます。

//emlist[todo.js][javascript]{
new Vue({
  el: '#app',
  data: {
    todo: "",
    list: ["hoge", "fuga"] //確認用にデータを入れる
  },
  methods: {
    sendTodo: function () {
      // data プロパティの list に追加
      this.list.push(this.todo)
      // 追加した todo は消しておく
      this.todo = ""
    }
  }
})
//}

//emlist[template.html][html]{
<div id="app">
  <!-- submitイベントでsendTodoが発火する -->
  <form v-on:submit.prevent="sendTodo">
    <input v-model="todo">
    <input type="submit" val="追加">
  </form>
  <ul v-for="item in list">
    <li>
      {{item}}
    </li>
  </ul>
</div>
//}

form の submit イベントにフックして sendTodo が発火するようにしています。sendTodo は methods プロパティに定義しています。list に現在の todo を push し、todo は空文字列を入れて初期化しています。

submit の後ろに .prevent を続けて書いてあるところがポイントです。これは修飾子@<fn>{v-on}と呼ばれるもので event.preventDefault() を呼ぶ処理になります。これを書くことにより、submit ボタンを押したときに通常の form の動作である POST をするところまで処理をさせません。

list に追加する処理ができたことにより、よりToDoリストらしくなってきました。

== ToDoを完了できるようにする

追加はできましたが、Todo を 完了にすることはまだできていませんでした。任意の ToDo を完了にするにはそのまま削除してしまうというのが手っ取り早くてよいのですが、ここは ToDo それぞれに状態を持たせてその状態を変化させることで完了の状態を表現したいと思います。

ToDo それぞれに状態を持たせるため、 list に追加する Todo は文字列ではなくオブジェクトにします。そのオブジェクトの状態を変化させるために、Todo をクリックしたら状態が変化するようにコードを書いていきます。

//emlist[todo.js][javascript]{
new Vue({
  el: '#app',
  data: {
    todo: "",
    list: []
  },
  methods: {
  	sendTodo: function () {
      // data プロパティの list に追加
      this.list.push({
        text: this.todo,
        status: 'todo'
      })
      // 追加した todo は消しておく
      this.todo = ""
    },
    doneTodo: function (item) {
      // statusの値を変える
      if (item.status == 'done') {
        item.status = 'todo'
      } else {
      	item.status = 'done'
      }
    }
  }
})
//}

//emlist[template.html][html]{
<div id="app">
  <!-- submitイベントでsendTodoが発火する -->
  <form v-on:submit.prevent="sendTodo">
    <input v-model="todo">
    <input type="submit" val="追加">
  </form>
  <ul v-for="item in list">
    <!-- doneTodo(item) でitem自身のstatusを変化させる -->
    <li v-on:click="doneTodo(item)">
      <span>
        status: {{item.status}}
      </span>
      <!-- v-ifでstatusによって表示の仕方を変える -->
      <s v-if="item.status == 'done'">
        {{item.text}}
      </s>
      <span v-else>
        {{item.text}}
      </span>
    </li>
  </ul>
</div>
//}

list に状態のあるオブジェクトが追加されるようになり、ToDo をクリックすることによりその状態が変化し、取り消し線が引かれるようになりました（@<img>{form_03}）。ToDoリストとして形になってきました。

//image[form_03][ToDoを完了できるようにする]{
//}

== まとめ

以上簡単なToDoリストを作ることで Vue.js のアプリケーション開発を体験していただきました。

実際のアプリケーションはこれ以上に複雑なものになると思われますが、基本はここで書いてきたコードの組み合わせで実現していくことになると思います。難しい所としては data プロパティの値をどう参照しどう変更していくかが各アプリケーションの複雑さに応じて難しくなっていくと思われます。Vue.js 配下のメソッドの行数が大きくなってきた場合、それは何かがおかしくなっている前兆ですので、そうなってきた際はコードを分割するなどして工夫していくのが良いと思います。

//footnote[v-on][APIリファレンス v-on：https://jp.vuejs.org/v2/api/#v-on]
