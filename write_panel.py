import base64,sys
b=sys.argv[1]
open(" E:/aisystem/byo-os/panel.html\,\wb\).write(base64.b64decode(b))
print(\Done:\,len(b))