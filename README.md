   # kadai1
２年　未来ロボティクス学科　ロボットシステム学の課題１
# 目次
・目的

・使用機器

・実行手順

・インストール

・LED点滅、消灯

・アンインストール

・引用

・ライセンス

# 目的

未来ロボティクス学科　セミスター４　ロボットシステム学の授業課題としてrasberry piを用いて仕組みを学ぶ

# 使用機器

・rasberry pi4

・rasberry pi4周辺機器

・パソコン

・ブレッドボード

・LED

・抵抗

# 実行手順
１rasberry piの22,39のピンにジャンパー線をさす

２コマンドを実行する


# インストール
    $ git clone https://github.com/Juntarok/kadai1.git
    $ cd kadai1
    $ make
    $ sudo insmod myled.ko
    $ sudo chmod 666 /dev/myled0

# LEDを点灯
    $ echo 0 >/dev/myled0
上記を入力するとLEDが点滅する

# LEDを消灯
    $ echo 1 >/dev/myled0
上記を入力するとLEDが消灯する

# アンインストール
    $ sudo rmmod myled
    
# 引用
   Ryuichi Ueda https://youtu.be/xQW8-FNuboo
   

# ライセンス
https://github.com/Juntarok/kadai1/blob/bcb01cea3d9003d5fd6d476cfb9bd8b581270dd2/LICENSE
