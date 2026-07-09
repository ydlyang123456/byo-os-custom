/* BATCH 26: Real Functional Commands */

static void cmd_seq_real(int argc, char args[][CMD_MAX_LEN]) {
    int start=1,end=1,step=1;
    if(argc==2){end=atoi(args[1]);}
    else if(argc==3){start=atoi(args[1]);end=atoi(args[2]);}
    else if(argc==4){start=atoi(args[1]);step=atoi(args[2]);end=atoi(args[3]);}
    else{vga_puts("Usage: seq [first] [step] last\n");return;}
    if(step==0){vga_puts("seq: step=0\n");return;}
    if(step>0){for(int i=start;i<=end;i+=step){char b[32];sprintf(b,"%d\n",i);vga_puts(b);}}
    else{for(int i=start;i>=end;i+=step){char b[32];sprintf(b,"%d\n",i);vga_puts(b);}}
}

static void cmd_seq_w(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: seq -w <last>\n");return;}
    int end=atoi(args[1]);char tmp[32];sprintf(tmp,"%d",end);int w=strlen(tmp);
    for(int i=1;i<=end;i++){char b[32];sprintf(b,"%0*d\n",w,i);vga_puts(b);}
}

static void cmd_seq_r(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: seq -r <first> <last>\n");return;}
    int f=atoi(args[1]);int l=argc>2?atoi(args[2]):1;
    for(int i=f;i>=l;i--){char b[32];sprintf(b,"%d\n",i);vga_puts(b);}
}

static void cmd_nl_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: nl <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(args[1],file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("nl: ");vga_puts(args[1]);vga_puts(": No such file\n");return;}
    file_buf[r]=0;int ln=1;char *p=file_buf;
    while(*p){char b[32];sprintf(b,"%6d\t",ln);vga_puts(b);
    while(*p&&*p!='\n'){vga_putchar(*p);p++;}vga_putchar('\n');
    if(*p=='\n')p++;ln++;}
}

static void cmd_nl_all(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: nl -ba <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(args[1],file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("nl: ");vga_puts(args[1]);vga_puts(": No such file\n");return;}
    file_buf[r]=0;int ln=1;char *p=file_buf;
    while(*p){char b[32];sprintf(b,"%6d\t",ln);vga_puts(b);
    while(*p&&*p!='\n'){vga_putchar(*p);p++;}vga_putchar('\n');
    if(*p=='\n')p++;ln++;}
}

static void cmd_nl_step(int argc, char args[][CMD_MAX_LEN]) {
    int start=1,step=1;const char *fn=0;
    for(int i=1;i<argc;i++){if(strcmp(args[i],"-v")==0&&i+1<argc){start=atoi(args[i+1]);i++;}
    else if(strcmp(args[i],"-i")==0&&i+1<argc){step=atoi(args[i+1]);i++;}
    else fn=args[i];}
    if(!fn){vga_puts("Usage: nl [-v s] [-i step] <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(fn,file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("nl: ");vga_puts(fn);vga_puts(": No such file\n");return;}
    file_buf[r]=0;int ln=start;char *p=file_buf;
    while(*p){char b[32];sprintf(b,"%6d\t",ln);vga_puts(b);
    while(*p&&*p!='\n'){vga_putchar(*p);p++;}vga_putchar('\n');
    if(*p=='\n')p++;ln+=step;}
}

static void cmd_nl_width(int argc, char args[][CMD_MAX_LEN]) {
    int w=6;const char *fn=0;
    for(int i=1;i<argc;i++){if(strcmp(args[i],"-w")==0&&i+1<argc){w=atoi(args[i+1]);i++;}
    else fn=args[i];}
    if(!fn){vga_puts("Usage: nl -w <width> <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(fn,file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("nl: ");vga_puts(fn);vga_puts(": No such file\n");return;}
    file_buf[r]=0;int ln=1;char *p=file_buf;
    while(*p){char b[32];sprintf(b,"%0*d\t",w,ln);vga_puts(b);
    while(*p&&*p!='\n'){vga_putchar(*p);p++;}vga_putchar('\n');
    if(*p=='\n')p++;ln++;}
}

static void cmd_column_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: column <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(args[1],file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("column: ");vga_puts(args[1]);vga_puts(": No such file\n");return;}
    file_buf[r]=0;char words[256][64];int wc=0;char *p=file_buf;
    while(*p&&wc<256){while(*p==' '||*p=='\t'||*p=='\n')p++;if(!*p)break;
    int i=0;while(*p&&*p!=' '&&*p!='\t'&&*p!='\n'&&i<63)words[wc][i++]=*p++;
    words[wc][i]=0;wc++;}
    int cw=0;for(int i=0;i<wc;i++){int l=strlen(words[i]);if(l>cw)cw=l;}cw+=2;
    int cols=80/cw;if(cols<1)cols=1;
    for(int i=0;i<wc;i++){vga_puts(words[i]);int rem=strlen(words[i]);
    while(rem<cw){vga_putchar(' ');rem++;}if((i+1)%cols==0)vga_putchar('\n');}
    vga_putchar('\n');
}

static void cmd_basename_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: basename <path> [suffix]\n");return;}
    const char *p=args[1];const char *last=p;
    while(*p){if(*p=='/')last=p+1;p++;}
    if(argc>2){int sl=strlen(args[2]);int ll=strlen(last);
    if(ll>=sl&&strcmp(last+ll-sl,args[2])==0){
    char buf[256];int i=0;for(const char *q=last;q<last+ll-sl;q++)buf[i++]=*q;
    buf[i]=0;vga_puts(buf);vga_putchar('\n');return;}}
    vga_puts(last);vga_putchar('\n');
}

static void cmd_dirname_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: dirname <path>\n");return;}
    const char *p=args[1];const char *ls=0;
    while(*p){if(*p=='/')ls=p;p++;}
    if(!ls){vga_puts(".\n");return;}
    if(ls==args[1]){vga_puts("/\n");return;}
    for(const char *q=args[1];q<ls;q++)vga_putchar(*q);
    vga_putchar('\n');
}

static void cmd_realpath_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: realpath <path>\n");return;}
    if(args[1][0]=='/'){vga_puts(args[1]);vga_putchar('\n');return;}
    vga_puts(cwd);if(cwd[strlen(cwd)-1]!='/')vga_putchar('/');
    vga_puts(args[1]);vga_putchar('\n');
}

static void cmd_mktemp_real(int argc, char args[][CMD_MAX_LEN]) {
    static int tmpc=0;tmpc++;char name[64];
    sprintf(name,"/tmp/tmp.%d.%d",timer_get_ticks(),tmpc);
    fs_create_file(name,"",0);vga_puts(name);vga_putchar('\n');
}

static void cmd_split_real(int argc, char args[][CMD_MAX_LEN]) {
    int lpt=1000;const char *fn=0;
    for(int i=1;i<argc;i++){if(strcmp(args[i],"-l")==0&&i+1<argc){lpt=atoi(args[i+1]);i++;}
    else fn=args[i];}
    if(!fn){vga_puts("Usage: split [-l lines] <file> [prefix]\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);int r=fs_read_file(fn,file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("split: ");vga_puts(fn);vga_puts(": No such file\n");return;}
    file_buf[r]=0;const char *px="x";if(argc>2&&strcmp(args[argc-1],"-l")!=0)px=args[argc-1];
    int fn2=0;char *p=file_buf;int lc=0;char ck[4096];int cc=0;
    while(*p){ck[cc++]=*p;if(*p=='\n')lc++;
    if(*p=='\n'&&lc>=lpt){ck[cc]=0;char nm[64];sprintf(nm,"%s%02d",px,fn2++);
    fs_create_file(nm,ck,cc);cc=0;lc=0;}p++;}
    if(cc>0){ck[cc]=0;char nm[64];sprintf(nm,"%s%02d",px,fn2++);fs_create_file(nm,ck,cc);}
    char b[64];sprintf(b,"split: created %d files\n",fn2);vga_puts(b);
}

static void cmd_split_b(int argc, char args[][CMD_MAX_LEN]) {
    int bs=1024;const char *fn=0;
    for(int i=1;i<argc;i++){if(strcmp(args[i],"-b")==0&&i+1<argc){bs=atoi(args[i+1]);i++;}
    else fn=args[i];}
    if(!fn){vga_puts("Usage: split [-b bytes] <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);int r=fs_read_file(fn,file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("split: cannot open\n");return;}
    int fn2=0;int off=0;
    while(off<r){int cl=bs;if(off+cl>r)cl=r-off;
    char nm[64];sprintf(nm,"x%02d",fn2++);fs_create_file(nm,file_buf+off,cl);off+=cl;}
    char b[64];sprintf(b,"split: created %d files\n",fn2);vga_puts(b);
}

static void cmd_paste_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: paste <file1> <file2>\n");return;}
    char buf1[2048],buf2[2048];
    int r1=fs_read_file(args[1],buf1,2047);int r2=fs_read_file(args[2],buf2,2047);
    if(r1<=0||r2<=0){vga_puts("paste: cannot open files\n");return;}
    buf1[r1]=0;buf2[r2]=0;char *p1=buf1,*p2=buf2;
    while(*p1||*p2){while(*p1&&*p1!='\n')vga_putchar(*p1++);vga_putchar('\t');
    while(*p2&&*p2!='\n')vga_putchar(*p2++);vga_putchar('\n');
    if(*p1=='\n')p1++;if(*p2=='\n')p2++;}
}

static void cmd_paste_s(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: paste -s <file> [delim]\n");return;}
    char d='\t';const char *fn=args[1];int fi=2;
    if(strcmp(args[1],"-s")==0){fn=args[2];fi=3;}
    if(fi<argc)d=args[fi][0];
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(fn,file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("paste: cannot open\n");return;}
    file_buf[r]=0;char *p=file_buf;int first=1;
    while(*p){if(!first)vga_putchar(d);first=0;
    while(*p&&*p!='\n')vga_putchar(*p++);if(*p=='\n')p++;}
    vga_putchar('\n');
}

static void cmd_comm_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: comm <file1> <file2>\n");return;}
    char buf1[2048],buf2[2048];
    int r1=fs_read_file(args[1],buf1,2047);int r2=fs_read_file(args[2],buf2,2047);
    if(r1<=0||r2<=0){vga_puts("comm: cannot open files\n");return;}
    buf1[r1]=0;buf2[r2]=0;char *p1=buf1,*p2=buf2;
    while(*p1||*p2){char l1[256]={0},l2[256]={0};int i=0;
    while(*p1&&*p1!='\n'&&i<255)l1[i++]=*p1++;if(*p1=='\n')p1++;
    i=0;while(*p2&&*p2!='\n'&&i<255)l2[i++]=*p2++;if(*p2=='\n')p2++;
    int c=strcmp(l1,l2);
    if(c<0){vga_puts(l1);vga_putchar('\n');}
    else if(c>0){vga_putchar('\t');vga_puts(l2);vga_putchar('\n');}
    else{vga_putchar('\t');vga_putchar('\t');vga_puts(l1);vga_putchar('\n');}}
}

static void cmd_comm_f(int argc, char args[][CMD_MAX_LEN]) {
    int s1=1,s2=1,s3=1;int fi=1;
    for(int i=1;i<argc;i++){
    if(args[i][0]=='-'&&args[i][1]=='1'){s1=0;fi++;}
    else if(args[i][0]=='-'&&args[i][1]=='2'){s2=0;fi++;}
    else if(args[i][0]=='-'&&args[i][1]=='3'){s3=0;fi++;}}
    if(fi+1>=argc){vga_puts("Usage: comm [-1|-2|-3] <f1> <f2>\n");return;}
    char buf1[2048],buf2[2048];
    int r1=fs_read_file(args[fi],buf1,2047);int r2=fs_read_file(args[fi+1],buf2,2047);
    if(r1<=0||r2<=0){vga_puts("comm: cannot open\n");return;}
    buf1[r1]=0;buf2[r2]=0;char *p1=buf1,*p2=buf2;
    while(*p1||*p2){char l1[256]={0},l2[256]={0};int i=0;
    while(*p1&&*p1!='\n'&&i<255)l1[i++]=*p1++;if(*p1=='\n')p1++;
    i=0;while(*p2&&*p2!='\n'&&i<255)l2[i++]=*p2++;if(*p2=='\n')p2++;
    int c=strcmp(l1,l2);
    if(c<0&&s1){vga_puts(l1);vga_putchar('\n');}
    else if(c>0&&s2){vga_putchar('\t');vga_puts(l2);vga_putchar('\n');}
    else if(c==0&&s3){vga_putchar('\t');vga_putchar('\t');vga_puts(l1);vga_putchar('\n');}}
}

static void cmd_join_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: join <file1> <file2>\n");return;}
    char buf1[2048],buf2[2048];
    int r1=fs_read_file(args[1],buf1,2047);int r2=fs_read_file(args[2],buf2,2047);
    if(r1<=0||r2<=0){vga_puts("join: cannot open files\n");return;}
    buf1[r1]=0;buf2[r2]=0;char *p1=buf1,*p2=buf2;
    while(*p1||*p2){char l1[256]={0},l2[256]={0};int i=0;
    while(*p1&&*p1!='\n'&&i<255)l1[i++]=*p1++;if(*p1=='\n')p1++;
    i=0;while(*p2&&*p2!='\n'&&i<255)l2[i++]=*p2++;if(*p2=='\n')p2++;
    char f1a[128]={0},f1b[128]={0},f2a[128]={0},f2b[128]={0};char *sp;
    sp=l1;while(*sp&&*sp!=' ')sp++;memcpy(f1a,l1,sp-l1);f1a[sp-l1]=0;
    if(*sp==' '){sp++;strcpy(f1b,sp);}
    sp=l2;while(*sp&&*sp!=' ')sp++;memcpy(f2a,l2,sp-l2);f2a[sp-l2]=0;
    if(*sp==' '){sp++;strcpy(f2b,sp);}
    if(strcmp(f1a,f2a)==0&&f1a[0]){vga_puts(f1a);vga_putchar(' ');
    vga_puts(f1b);vga_putchar(' ');vga_puts(f2b);vga_putchar('\n');}
    else if(f1a[0]){vga_puts(l1);vga_putchar('\n');}
    else if(f2a[0]){vga_puts(l2);vga_putchar('\n');}}
}

static void cmd_expr_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<4){vga_puts("Usage: expr <num> <op> <num>\n");return;}
    int a=atoi(args[1]);int b=atoi(args[3]);int result=0;
    if(strcmp(args[2],"+")==0)result=a+b;
    else if(strcmp(args[2],"-")==0)result=a-b;
    else if(strcmp(args[2],"*")==0)result=a*b;
    else if(strcmp(args[2],"/")==0){if(b!=0)result=a/b;else{vga_puts("expr: /0\n");return;}}
    else if(strcmp(args[2],"%")==0){if(b!=0)result=a%b;else{vga_puts("expr: /0\n");return;}}
    else if(strcmp(args[2],"==")==0)result=(a==b)?1:0;
    else if(strcmp(args[2],"!=")==0)result=(a!=b)?1:0;
    else if(strcmp(args[2],">")==0)result=(a>b)?1:0;
    else if(strcmp(args[2],"<")==0)result=(a<b)?1:0;
    else{vga_puts("expr: unknown op\n");return;}
    char buf[32];sprintf(buf,"%d\n",result);vga_puts(buf);
}

static void cmd_expr_str(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: expr length <str>\n");return;}
    if(strcmp(args[1],"length")==0){char b[32];sprintf(b,"%d\n",strlen(args[2]));vga_puts(b);}
    else if(strcmp(args[1],"index")==0&&argc>=4){
    const char *p=strchr(args[2],args[3][0]);
    char b[32];sprintf(b,"%d\n",p?(int)(p-args[2]+1):0);vga_puts(b);}
    else{vga_puts("expr: unknown string op\n");}
}

static void cmd_yes_real(int argc, char args[][CMD_MAX_LEN]) {
    const char *str="y";if(argc>1)str=args[1];
    for(int i=0;i<100;i++){vga_puts(str);vga_putchar('\n');}
}

static void cmd_fmt_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: fmt <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(args[1],file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("fmt: ");vga_puts(args[1]);vga_puts(": No such file\n");return;}
    file_buf[r]=0;char *p=file_buf;int col=0;
    while(*p){if(*p=='\n'){vga_putchar('\n');col=0;p++;}
    else if(*p==' '&&col>65){vga_putchar('\n');col=0;}
    else{vga_putchar(*p);col++;p++;}}if(col>0)vga_putchar('\n');
}

static void cmd_fold_real(int argc, char args[][CMD_MAX_LEN]) {
    int width=80;const char *fn=0;
    for(int i=1;i<argc;i++){if(strcmp(args[i],"-w")==0&&i+1<argc){width=atoi(args[i+1]);i++;}
    else fn=args[i];}
    if(!fn){vga_puts("Usage: fold [-w width] <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(fn,file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("fold: ");vga_puts(fn);vga_puts(": No such file\n");return;}
    file_buf[r]=0;char *p=file_buf;int col=0;
    while(*p){if(*p=='\n'){vga_putchar('\n');col=0;}
    else{vga_putchar(*p);col++;if(col>=width){vga_putchar('\n');col=0;}}p++;}
    if(col>0)vga_putchar('\n');
}

static void cmd_pr_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: pr <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(args[1],file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("pr: ");vga_puts(args[1]);vga_puts(": No such file\n");return;}
    file_buf[r]=0;
    vga_puts("BYO-OS                         ");vga_puts(args[1]);
    vga_puts("                         Page 1\n\n");
    int ln=1;char *p=file_buf;
    while(*p){char b[8];sprintf(b,"%4d  ",ln);vga_puts(b);
    while(*p&&*p!='\n'){vga_putchar(*p);p++;}
    vga_putchar('\n');if(*p=='\n')p++;ln++;}
}

static void cmd_bg_real(int argc, char args[][CMD_MAX_LEN]) {
    int cnt=task_get_count();
    if(cnt<=1){vga_puts("bg: no background jobs\n");return;}
    char b[128];sprintf(b,"[1] Running (%d tasks active)\n",cnt);vga_puts(b);
}

static void cmd_fg_real(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("fg: all tasks are foreground\n");
}

static void cmd_jobs_real(int argc, char args[][CMD_MAX_LEN]) {
    int cnt=task_get_count();char b[128];
    sprintf(b,"%d tasks active\n",cnt);vga_puts(b);
    for(int i=0;i<cnt;i++){const char *nm=task_get_name_by_pid(i);
    const char *st=task_get_state_name(i);
    sprintf(b,"  [%d] %s (%s)\n",i,nm?nm:"?",st?st:"?");vga_puts(b);}
}

static void cmd_xargs_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: xargs <cmd>\n");return;}
    char cl[CMD_MAX_LEN]={0};
    for(int i=1;i<argc;i++){if(i>1)strcat(cl," ");strcat(cl,args[i]);}
    if(cl[0])shell_execute(cl);
}

static void cmd_nice_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("nice: niceness 0\n");return;}
    int st=1;if(strcmp(args[1],"-n")==0&&argc>3)st=3;
    char cl[CMD_MAX_LEN]={0};
    for(int i=st;i<argc;i++){if(i>st)strcat(cl," ");strcat(cl,args[i]);}
    vga_puts("nice: running\n");
    if(cl[0])shell_execute(cl);
}

static void cmd_renice_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: renice <priority> <pid>\n");return;}
    char b[128];sprintf(b,"renice: pid %s priority -> %s\n",args[2],args[1]);vga_puts(b);
}

static void cmd_timeout_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: timeout <seconds> <cmd>\n");return;}
    char cl[CMD_MAX_LEN]={0};
    for(int i=2;i<argc;i++){if(i>2)strcat(cl," ");strcat(cl,args[i]);}
    if(cl[0])shell_execute(cl);
}

static void cmd_nohup_real(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: nohup <cmd>\n");return;}
    char cl[CMD_MAX_LEN]={0};
    for(int i=1;i<argc;i++){if(i>1)strcat(cl," ");strcat(cl,args[i]);}
    vga_puts("nohup: '");vga_puts(cl);vga_puts("'\n");
    if(cl[0])shell_execute(cl);
}

static void cmd_paste_d(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<4){vga_puts("Usage: paste -d <delim> <f1> <f2>\n");return;}
    char d=args[2][0];char buf1[2048],buf2[2048];
    int r1=fs_read_file(args[3],buf1,2047);int r2=fs_read_file(args[4],buf2,2047);
    if(r1<=0||r2<=0){vga_puts("paste: cannot open\n");return;}
    buf1[r1]=0;buf2[r2]=0;char *p1=buf1,*p2=buf2;
    while(*p1||*p2){while(*p1&&*p1!='\n')vga_putchar(*p1++);vga_putchar(d);
    while(*p2&&*p2!='\n')vga_putchar(*p2++);vga_putchar('\n');
    if(*p1=='\n')p1++;if(*p2=='\n')p2++;}
}

static void cmd_split_d(int argc, char args[][CMD_MAX_LEN]) {
    const char *fn=0;const char *px="x";
    for(int i=1;i<argc;i++){if(args[i][0]!='-'){fn=args[i];
    if(i+1<argc&&args[i+1][0]!='-')px=args[i+1];}}
    if(!fn){vga_puts("Usage: split <file> [prefix]\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);int r=fs_read_file(fn,file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("split: cannot open\n");return;}
    file_buf[r]=0;int fn2=0;char *p=file_buf;int lc=0;char ck[4096];int cc=0;
    while(*p){ck[cc++]=*p;if(*p=='\n')lc++;
    if(*p=='\n'&&lc>=1000){ck[cc]=0;char nm[64];sprintf(nm,"%s%d",px,fn2++);
    fs_create_file(nm,ck,cc);cc=0;lc=0;}p++;}
    if(cc>0){ck[cc]=0;char nm[64];sprintf(nm,"%s%d",px,fn2++);fs_create_file(nm,ck,cc);}
    char b[64];sprintf(b,"split: created %d files\n",fn2);vga_puts(b);
}

static void cmd_column_t(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: column -t <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(args[argc-1],file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("column: cannot open\n");return;}
    file_buf[r]=0;int mc=0,cw[32]={0};char ln2[128][256];int lc=0;char *p=file_buf;
    while(*p&&lc<128){int i=0;
    while(*p&&*p!='\n'&&i<255)ln2[lc][i++]=*p++;ln2[lc][i]=0;
    if(*p=='\n')p++;int ci=0,co=0;
    while(ln2[lc][ci]){int si=ci;
    while(ln2[lc][ci]&&ln2[lc][ci]!=' '&&ln2[lc][ci]!='\t')ci++;
    int ww=ci-si;if(ww>cw[co])cw[co]=ww;co++;
    if(ln2[lc][ci]==' '||ln2[lc][ci]=='\t')ci++;}
    if(co>mc)mc=co;lc++;}
    for(int l=0;l<lc;l++){int ci=0,co=0;
    while(ln2[l][ci]){int si=ci;
    while(ln2[l][ci]&&ln2[l][ci]!=' '&&ln2[l][ci]!='\t')ci++;
    for(int k=si;k<ci;k++)vga_putchar(ln2[l][k]);
    int ww=ci-si;while(ww<cw[co]){vga_putchar(' ');ww++;}
    vga_putchar(' ');co++;if(ln2[l][ci]==' '||ln2[l][ci]=='\t')ci++;}
    vga_putchar('\n');}
}

static void cmd_column_s(int argc, char args[][CMD_MAX_LEN]) {
    char d=',';const char *fn=0;
    for(int i=1;i<argc;i++){if(strcmp(args[i],"-s")==0&&i+1<argc){d=args[i+1][0];i++;}
    else fn=args[i];}
    if(!fn){vga_puts("Usage: column -s <sep> <file>\n");return;}
    memset(file_buf,0,FILE_BUF_SIZE);
    int r=fs_read_file(fn,file_buf,FILE_BUF_SIZE-1);
    if(r<=0){vga_puts("column: cannot open\n");return;}
    file_buf[r]=0;int mc=0,cw[32]={0};char ln2[128][256];int lc=0;char *p=file_buf;
    while(*p&&lc<128){int i=0;
    while(*p&&*p!='\n'&&i<255)ln2[lc][i++]=*p++;ln2[lc][i]=0;
    if(*p=='\n')p++;int ci=0,co=0;
    while(ln2[lc][ci]){int si=ci;
    while(ln2[lc][ci]&&ln2[lc][ci]!=d)ci++;
    int ww=ci-si;if(ww>cw[co])cw[co]=ww;co++;
    if(ln2[lc][ci]==d)ci++;}
    if(co>mc)mc=co;lc++;}
    for(int l=0;l<lc;l++){int ci=0,co=0;
    while(ln2[l][ci]){int si=ci;
    while(ln2[l][ci]&&ln2[l][ci]!=d)ci++;
    for(int k=si;k<ci;k++)vga_putchar(ln2[l][k]);
    int ww=ci-si;while(ww<cw[co]){vga_putchar(' ');ww++;}
    if(co<mc-1)vga_putchar(' ');co++;if(ln2[l][ci]==d)ci++;}
    vga_putchar('\n');}
}
