# Estado técnico inicial

## Objetivo

Mantener la aplicación VB6 original —su interfaz, formularios y modos A–D— y reemplazar únicamente la compatibilidad del control multimedia antiguo, siempre en una copia aislada.

## Evidencia confirmada

1. El respaldo original verificado contiene un `Gold.exe` PE32/x86 de 1,982,919 bytes (SHA-256 registrado en el README).
2. `frmPlayer` contiene tres controles ActiveX `MediaPlayerCtl.MediaPlayer`. En el diseñador recuperado aparecen los nombres `MpSello`, `MP` y `MP`; eso todavía no demuestra el rol funcional exacto de cada instancia.
3. El CLSID inspeccionado es `{22D6F312-B0F6-11D0-94AB-0080C74C7E95}`.
4. La interfaz predeterminada reportada es `IMediaPlayer2`, IID `{20D4F5E0-5475-11D2-9774-0000F80855E6}`, `TYPEKIND=TKIND_DISPATCH`, con 192 funciones.
5. El origen de eventos predeterminado reportado es `_MediaPlayerEvents`, IID `{2D3A4C40-E711-11D0-94AB-0080C74C7E95}`, con 20 eventos/métodos.
6. El informe COM enumera tres puntos de conexión; los otros dos IIDs son `{33222211-5E5E-11D2-9E8E-0000F8085981}` y `{B6CD6553-E9CB-11D0-821F-00A0C91F9CA0}`.
7. La activación COM del control original en el Windows inspeccionado fue correcta. Eso no demuestra que Gold reciba/procese los eventos ni que avance la pauta.

## Resultado técnico

No se debe tratar la incidencia como simple ausencia de registro COM: la clase original pudo activarse. La reparación tiene que conservar la interfaz Automation, los eventos de salida y el ciclo de vida OLE del ActiveX que VB6 hospeda.

## Restricciones

No tocar el ejecutable original, su respaldo, `Gold.INI`, `DBMusica.mdb`, `C:\GOLD`, `C:\Musica`, Radio Aguán, Gold_FullClone ni GOLD PREMIUM NEXT GENERATION.
