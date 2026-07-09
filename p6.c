static void cmd_grep(const char* a) {
    int ci=0,inv=0,ln=0; const char*p=a;
    while(*p=='-'){p++;while(*p&&*p!=' '){if(*p=='i')ci=1;else if(*p=='v')inv=1;else if(*p=='n')ln=1;p++;}while(*p==' ')p++;}
    char pat[64],fn[64];int pi=0;while(*p&&*p!=' '){pat[pi++]=*p++;}pat[pi]=0;while(*p==' ')p++;int fi=0;while(*p&&*p!=' '){fn[fi++]=*p++;}fn[fi]=0;
    if(pi==0||fi==0){vga_puts("Usage: grep [-i-v-n] pat file\n");return;}
    if(!fs_file_exists(fn)){vga_puts("No such file\n");return;}
    char buf[2048];int sz=fs_read_file(fn,buf,2047);if(sz<=0)return;buf[sz]=0;
    int line=1;const char*ls=buf;
    while(*ls){const char*le=ls;while(*le&&*le!='\n')le++;int ll=(int)(le-ls);char lb[256];if(ll>255)ll=255;memcpy(lb,ls,ll);lb[ll]=0;
    const char*mt=strstr(lb,pat);
    if(ci&&!mt){char lo[256];for(int i=0;i<=ll;i++)lo[i]=lb[i];char lp[64];int k=0;while(pat[k]){lp[k]=(pat[k]>='A'&&pat[k]<='Z')?pat[k]+32:pat[k];k++;}lp[k]=0;char*lh=lo;while(*lh){if(*lh>='A'&&*lh<='Z')*lh+=32;lh++;}mt=strstr(lo,lp);}
    if((mt&&!inv)||(!mt&&inv)){if(ln){vga_put_dec(line);vga_puts(":");}vga_puts(lb);vga_puts("\n");}
    line++;if(*le=='\n')ls=le+1;else break;}
}
static void cmd_sort(const char* fn) {
    if(!fs_file_exists(fn)){vga_puts("No such file\n");return;}
    char buf[2048];int sz=fs_read_file(fn,buf,2047);if(sz<=0)return;buf[sz]=0;
    char lines[64][128];int nl=0;const char*p=buf;
    while(*p&&nl<64){int i=0;while(*p&&*p!='\n'&&i<127){lines[nl][i++]=*p++;}lines[nl][i]=0;nl++;if(*p=='\n')p++;}
    for(int i=0;i<nl-1;i++)for(int j=0;j<nl-i-1;j++)if(strcmp(lines[j],lines[j+1])>0){char t[128];strcpy(t,lines[j]);strcpy(lines[j],lines[j+1]);strcpy(lines[j+1],t);}
    for(int i=0;i<nl;i++){vga_puts(lines[i]);vga_puts("\n");}
}
static void cmd_uniq(const char* fn) {
    if(!fs_file_exists(fn)){vga_puts("No such file\n");return;}
    char buf[2048];int sz=fs_read_file(fn,buf,2047);if(sz<=0)return;buf[sz]=0;
    char prev[128]="";const char*p=buf;
    while(*p){char l[128];int i=0;while(*p&&*p!='\n'&&i<127){l[i++]=*p++;}l[i]=0;if(*p=='\n')p++;
    if(strcmp(l,prev)!=0){vga_puts(l);vga_puts("\n");strcpy(prev,l);}}
}
static void cmd_wc(const char* fn) {
    if(!fs_file_exists(fn)){vga_puts("No such file\n");return;}
    char buf[4096];int sz=fs_read_file(fn,buf,4095);if(sz<=0)return;
    int lines=0,words=0,inw=0;
    for(int i=0;i<sz;i++){if(buf[i]=='\n')lines++;if(buf[i]==' '||buf[i]=='\n'||buf[i]=='\t')inw=0;else if(!inw){inw=1;words++;}}
    vga_put_dec(lines);vga_puts(" ");vga_put_dec(words);vga_puts(" ");vga_put_dec(sz);vga_puts(" ");vga_puts(fn);vga_puts("\n");
}
static void cmd_head(const char* a) {
    int n=10;const char*p=a;if(startswith(p,"-n ")){p+=3;n=atoi(p);while(*p&&*p!=' ')p++;while(*p==' ')p++;}
    if(!fs_file_exists(p)){vga_puts("No such file\n");return;}
    char buf[4096];int sz=fs_read_file(p,buf,4095);if(sz<=0)return;buf[sz]=0;
    int printed=0;const char*s=buf;while(*s&&printed<n){vga_putchar(*s);if(*s=='\n')printed++;s++;}
}
static void cmd_tail(const char* a) {
    int n=10;const char*p=a;if(startswith(p,"-n ")){p+=3;n=atoi(p);while(*p&&*p!=' ')p++;while(*p==' ')p++;}
    if(!fs_file_exists(p)){vga_puts("No such file\n");return;}
    char buf[4096];int sz=fs_read_file(p,buf,4095);if(sz<=0)return;buf[sz]=0;
    int total=1;for(int i=0;i<sz;i++)if(buf[i]=='\n')total++;
    int skip=total-n;if(skip<0)skip=0;
    const char*s=buf;int line=0;while(*s){if(line>=skip)vga_putchar(*s);if(*s=='\n')line++;s++;}
}
static void cmd_cut(const char* a) {
    char delim='\t';int field=1;const char*p=a;
    if(startswith(p,"-d")){p+=2;if(*p)delim=*p;p++;while(*p==' ')p++;}
    if(startswith(p,"-f")){p+=2;field=atoi(p);while(*p&&*p!=' ')p++;while(*p==' ')p++;}
    if(!fs_file_exists(p)){vga_puts("No such file\n");return;}
    char buf[2048];int sz=fs_read_file(p,buf,2047);if(sz<=0)return;buf[sz]=0;
    const char*ln=buf;while(*ln){int f=1;const char*s=ln;while(*s&&*s!='\n'){if(f==field)vga_putchar(*s);if(*s==delim)f++;s++;}
    vga_puts("\n");if(*s=='\n')s++;else break;ln=s;}
}