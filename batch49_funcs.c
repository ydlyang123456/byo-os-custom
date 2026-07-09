/* ===== Batch 49: Cloud, Monitoring, Office, Science ===== */
static void cmd_aws49(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("aws: AWS CLI\nUsage: aws <s3|ec2|iam|lambda|cloudformation>\n"); return; }
    if (strcmp(args[1], "s3") == 0 && argc > 2 && strcmp(args[2], "ls") == 0) {
        vga_puts("2025-01-15 12:00        42 my-bucket\n2025-01-15 12:00        18 logs-bucket\n");
    } else if (strcmp(args[1], "ec2") == 0 && argc > 2 && strcmp(args[2], "describe-instances") == 0) {
        vga_puts("INSTANCE_ID     STATE       TYPE          NAME\ni-0a1b2c3d4e5f  running     t2.micro      my-vm\ni-1b2c3d4e5f6g  stopped     t2.small      test-vm\n");
    } else if (strcmp(args[1], "iam") == 0) {
        vga_puts("User: root\nARN: arn:aws:iam::123456789012:user/root\n");
    } else { vga_puts("aws: command executed\n"); }
}
static void cmd_gcloud49(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("gcloud: Google Cloud CLI\nUsage: gcloud <compute|storage|functions|run>\n"); return; }
    if (strcmp(args[1], "compute") == 0 && argc > 2 && strcmp(args[2], "instances") == 0) {
        vga_puts("NAME          ZONE           STATUS   MACHINE_TYPE\nmy-vm         us-central1-a  RUNNING  e2-micro\ntest-vm       us-east1-b     STOPPED  e2-small\n");
    } else if (strcmp(args[1], "storage") == 0) {
        vga_puts("BUCKET_NAME    LOCATION    STORAGE_CLASS\nmy-bucket      US          STANDARD\n");
    } else { vga_puts("gcloud: command executed\n"); }
}
static void cmd_az49(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("az: Azure CLI\nUsage: az <vm|storage|account|network>\n"); return; }
    if (strcmp(args[1], "vm") == 0 && argc > 2 && strcmp(args[2], "list") == 0) {
        vga_puts("Name          ResourceGroup    Location    Status\nmy-vm         myRg             eastus      Running\ntest-vm       myRg             westus      Stopped\n");
    } else if (strcmp(args[1], "storage") == 0) {
        vga_puts("ACCOUNT_NAME  RESOURCE_GROUP  LOCATION\nmystorage     myRg             eastus\n");
    } else { vga_puts("az: command executed\n"); }
}
static void cmd_terraform49(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("terraform: infrastructure as code\nUsage: terraform <init|plan|apply|destroy|state>\n"); return; }
    if (strcmp(args[1], "init") == 0) {
        vga_puts("Initializing the backend...\nInitializing provider plugins...\nTerraform has been successfully initialized!\n");
    } else if (strcmp(args[1], "plan") == 0) {
        vga_puts("Terraform will perform the following actions:\n  + aws_instance.web will be created\n  + aws_security_group.allow_http will be created\nPlan: 2 to add, 0 to change, 0 to destroy.\n");
    } else if (strcmp(args[1], "apply") == 0) {
        vga_puts("Apply complete! Resources: 2 added, 0 changed, 0 destroyed.\n");
    } else if (strcmp(args[1], "state") == 0) {
        vga_puts("Resources: 2\n  aws_instance.web: id=i-0a1b2c3d4e5f\n  aws_security_group.allow_http: id=sg-12345678\n");
    } else { vga_puts("terraform: command executed\n"); }
}
static void cmd_ansible49(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("ansible: IT automation\nUsage: ansible <playbook|inventory|vault>\n"); return; }
    if (strcmp(args[1], "playbook") == 0) {
        vga_puts("PLAY [all] ********************************************************\nTASK [Gathering Facts] *******************************************\nok: [web1]\nok: [web2]\n\nTASK [Install nginx] **********************************************\nchanged: [web1]\nchanged: [web2]\n\nPLAY RECAP *******************************************************\nweb1  : ok=2  changed=1  unreachable=0  failed=0\nweb2  : ok=2  changed=1  unreachable=0  failed=0\n");
    } else if (strcmp(args[1], "inventory") == 0) {
        vga_puts("[webservers]\nweb1 ansible_host=10.0.0.1\nweb2 ansible_host=10.0.0.2\n\n[dbservers]\ndb1 ansible_host=10.0.1.1\n");
    } else { vga_puts("ansible: command executed\n"); }
}
static void cmd_puppet49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("puppet: configuration management\nUsage: puppet <apply|agent|master|module>\n");
}
static void cmd_chef49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("chef: infrastructure automation\nUsage: chef <client|solo|knife>\n");
}
static void cmd_salt49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("salt: event-driven infrastructure management\nUsage: salt <minion|master|key>\n");
}

/* Monitoring */
static void cmd_prometheus49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("prometheus: monitoring and alerting\nStatus: Active\nTargets: 3\nRules: 5\nAlerts: 0\n");
}
static void cmd_grafana49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("grafana: analytics and visualization\nVersion: 10.2.2\nStatus: running on http://localhost:3000\nDashboards: 5\nData sources: 3\n");
}
static void cmd_nagios49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Nagios Core 4.4.7\nStatus: Running\nHosts: 10 (9 up, 1 down)\nServices: 45 (42 OK, 2 WARNING, 1 CRITICAL)\n");
}
static void cmd_zabbix49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Zabbix 6.4 LTS\nStatus: running\nHosts: 10 (8 enabled, 2 disabled)\nTriggers: 25 (20 OK, 3 WARNING, 2 PROBLEM)\nProblems: 2\n");
}
static void cmd_datadog49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("datadog: cloud-scale monitoring\nStatus: active\nMetrics: 12345/min\nEvents: 567/min\nLogs: 8901/min\n");
}
static void cmd_newrelic49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("newrelic: observability platform\nStatus: connected\nApplications: 5\nAlerts: 3\nAPM score: 98%\n");
}

/* Office / Document */
static void cmd_libreoffice49(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("libreoffice: office suite\nUsage: libreoffice --calc/--writer/--impress <file>\n"); return; }
    vga_puts("LibreOffice 7.6.2\nOpening: "); vga_puts(argc > 2 ? args[2] : "document"); vga_puts("\n");
}
static void cmd_pandoc49(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: pandoc <input> -o <output>\n"); return; }
    vga_puts("pandoc: universal document converter\nConverting "); vga_puts(args[1]); vga_puts(" to "); vga_puts(argc > 3 ? args[3] : "output"); vga_puts("\n");
}
static void cmd_latex49(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: latex <file.tex>\n"); return; }
    vga_puts("This is pdfTeX, Version 3.141592653-2.6-1.40.24\nOutput written on "); vga_puts(args[1]); vga_puts(".dvi\n");
}
static void cmd_bibtex49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("bibtex: bibliography processor\nUsage: bibtex <auxfile>\n");
}
static void cmd_pandoc2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("pandoc 3.1.2\nUsage: pandoc <file> -o <output>\nFormats: markdown, html, pdf, docx, odt, latex\n");
}
static void cmd_wkhtmltopdf49(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: wkhtmltopdf <url> <output.pdf>\n"); return; }
    vga_puts("Loading page...\nPrinting...\nDone: "); vga_puts(args[2]); vga_puts("\n");
}
static void cmd_weasyprint49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("weasyprint: HTML/CSS to PDF converter\nUsage: weasyprint <input.html> <output.pdf>\n");
}
static void cmd_ghostscript49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("GPL Ghostscript 10.01.2 (2023-06-30)\nUsage: gs <file.ps>\n");
}

/* Scientific Computing */
static void cmd_python349(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Python 3.11.6\n>>> print('Hello')\nHello\n>>> exit()\n"); return; }
    if (strcmp(args[1], "--version") == 0) vga_puts("Python 3.11.6\n");
    else if (strcmp(args[1], "-c") == 0 && argc > 2) { vga_puts(args[2]); vga_putchar('\n'); }
    else { vga_puts("Python: executing "); vga_puts(args[1]); vga_putchar('\n'); }
}
static void cmd_octave49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("GNU Octave, version 8.4.0\n>>> a = [1 2 3; 4 5 6]\na =\n   1   2   3\n   4   5   6\n>>> det(a)\nans = -3\n");
}
static void cmd_R49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("R version 4.3.2 (2023-10-31)\n> c(1,2,3)\n[1] 1 2 3\n> mean(c(1,2,3))\n[1] 2\n");
}
static void cmd_scipy49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("scipy 1.11.4\nModules: optimize, integrate, interpolate, signal, linalg\n");
}
static void cmd_numpy49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("numpy 1.26.2\n>>> import numpy as np\n>>> np.array([1,2,3])\narray([1, 2, 3])\n");
}
static void cmd_pandas49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("pandas 2.1.4\n>>> import pandas as pd\n>>> pd.DataFrame({'a':[1,2]})\n   a\n0  1\n1  2\n");
}
static void cmd_matplotlib49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("matplotlib 3.8.2\nBackend: TkAgg\n>>> plt.plot([1,2,3])\n>>> plt.show()\n");
}
static void cmd_jupyter49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Jupyter Notebook 7.0.6\nServer running at http://localhost:8888\nNotebooks: 5\n");
}
static void cmd_sympy49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("SymPy 1.12\n>>> from sympy import *\n>>> x = Symbol('x')\n>>> integrate(x**2, x)\nx**3/3\n");
}
static void cmd_gnuplot49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("gnuplot 5.4 patchlevel 8\nTerminal type set to 'dumb'\nPlotting...\n");
}
static void cmd_maxima49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Maxima 5.47.0\n(%i1) integrate(x^2, x);\n(%o1) x^3/3\n");
}
static void cmd_sage49(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("SageMath 10.2\nsage: factor(x^2 - 1)\n(x - 1)*(x + 1)\n");
}
