# M5Stack-Avatar-collection

M5StackでAvatarを表示するアプリです。

Avatar表示は、robo8080さんの[M5Stack_WebRadio_Avator](https://github.com/robo8080/M5Stack_WebRadio_Avator)をベースにさせていただきました。
M5Stack-avatarのオリジナルはmeganetaaanさんの[m5stack-avatar](https://github.com/meganetaaan/m5stack-avatar)です。

背景にJPGファイルを使用したかったのでm5stack-avatarの古いバージョンを利用しています。

# 使い方(Usage)

buildフォルダにあるbinファイル,jpgフォルダ,jsonフォルダをmicroSDカードにコピーします。
[M5Stack LovyanLauncher](https://github.com/lovyan03/M5Stack_LovyanLauncher)から起動します。
LovyanLauncherの詳しい使い方は下記のブログを参照してください。

[M5Stack LovyanLauncherの使い方｜ラズパイ好きの日記](https://raspberrypi.mongonta.com/howto-use-m5stack-lovyanlauncher/)

# カスタマイズのポイント
sketchbookフォルダにソースや元画像が入っています。
## 背景
背景はavatar_???_bg.cにデータがあります。まずはavatar_???_bg.jpgを作成します。
* サイズは320×240
* MicroSoftペイントは保存すればそのまま使えます。イラストレーターの場合はプログレッシブオフ、マット無しでWeb用に保存をします。
* 背景を作成する場合は目が移動する部分のマージンを取る必要があるので注意してください。(bgColorと同色)

### JPGデータをCのソースへ変換する
下記リンクにあるbin2code.pyを使用するとcのコードに変換できます。（要Pythonの実行環境）
https://github.com/m5stack/M5Stack/tree/master/tools
## 目と口
目と口の変更はavatar.cppとavatar.hの変更をします。変更は下記のCommitが参考になるかと思います。

[Change from Fugu to UMA](https://github.com/mongonta0716/M5Stack-Avatar-uma/commit/8da0441fec0a3a6d0a4a4a33f9aa40b7c8aa51c7?diff=unified)

## 色について
下記のIn_eSPI.hの500行目ぐらいに定義があります。

https://github.com/m5stack/M5Stack/blob/master/src/utility/In_eSPI.h

自分で色を作成したい場合はM5.Lcd.color565(int r, int g, int b)を使うと変換できます。

例、肌色
const unsigned int HADAIRO = M5.Lcd.color565(255,233,218);

# Requirement

コンパイルする場合は、以下のライブラリが必要です。
* [M5Stack-SD-Updater](https://github.com/tobozo/M5Stack-SD-Updater)

# Licence
[GPLv3](https://github.com/mongonta0716/M5Stack-Avatar-collection/blob/master/LICENSE)

# Author
[Takao Akaki](https://twitter.com/mongonta555)
