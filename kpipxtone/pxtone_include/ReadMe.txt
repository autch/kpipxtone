ピストンDLLを使うとピストンコラージュで制作した曲を
他のプログラムで再生させることができます。

使用に制限はありませんが、もしよければ
このフォルダにある pxtone.png をロゴとして使ってください。
加工していただいてもかまいません。

バグがあれば報告ください。
URL：http://hp.vector.co.jp/authors/VA022293/



v.0.9.1.9:
  引数の型をいくらか変えました。 BOOL -> bool、long -> int など。

v.0.9.1.8:
  pxtone_Tune_Start() の引数にボリュームを追加。

v.0.9.1.7:
  pxtone.lib なし。

v.0.9.1.6 :
  pxtone_Noise_Create() / pxtone_Noise_Create_FromMemory() を追加。

v.-.-.-.- 色々変更はあったと思う..

v.0.7.1.6 :
  pxtone_Release() の後で pxtone_Ready() を呼ぶと落ちるバグを修正。
  pxtone_Tune_Vomit() 等を修正。

v.0.7.1.5 : (改名が多くて申しわけない)
  pxtone_Tune_Read() を追加。
  pxtone_Tune_Vomit() を追加。
  pxtone_ResetSampling()  を pxtone_reset() に改名。
  pxtone_Tune_Play()      を pxtone_Tune_Start() に改名。
  pxtone_Tune_IsPlaying() を pxtone_Tune_IsStreaming() に改名。

v.0.7.1.2 : C ソースに対応。

v.0.6.2.0 : 関数名 pxtone_Tune_GetLastError() を pxtone_GetLastError() に変更。
