/* === Batch 36: Container + Cloud + Database + Web Server === */

/* docker - container runtime */
static void cmd_docker(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: docker [ps|images|run|stop|rm|build|pull|push|logs|exec]\n");
        return;
    }
    if (strcmp(args[1], "ps") == 0) {
        vga_puts("CONTAINER ID  IMAGE          STATUS       NAMES\n");
        vga_puts("a1b2c3d4e5f6  nginx:latest   Up 2 hours   web-server\n");
        vga_puts("b2c3d4e5f6a1  redis:7        Up 3 hours   cache\n");
        vga_puts("c3d4e5f6a1b2  postgres:15    Up 1 day     database\n");
    } else if (strcmp(args[1], "images") == 0) {
        vga_puts("REPOSITORY   TAG     IMAGE ID       SIZE\n");
        vga_puts("nginx        latest  a1b2c3d4e5f6   187MB\n");
        vga_puts("redis        7       b2c3d4e5f6a1   138MB\n");
        vga_puts("postgres     15      c3d4e5f6a1b2   379MB\n");
        vga_puts("python       3.11    d4e5f6a1b2c3   912MB\n");
    } else if (strcmp(args[1], "run") == 0) {
        vga_puts("Unable to find image '")
        if (argc > 2) vga_puts(args[2]);
        vga_puts(":latest' locally\n");
        vga_puts("Pulling from library...\n");
        vga_puts("Status: Downloaded newer image\n");
        vga_puts("Container started.\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_puts("Container stopped.\n");
    } else if (strcmp(args[1], "rm") == 0) {
        vga_puts("Container removed.\n");
    } else if (strcmp(args[1], "logs") == 0) {
        vga_puts("2026-07-09T00:00:00Z [nginx] Starting...\n");
        vga_puts("2026-07-09T00:00:01Z [nginx] Listening on port 80\n");
        vga_puts("2026-07-09T00:00:02Z [nginx] Worker process started\n");
    } else if (strcmp(args[1], "exec") == 0) {
        vga_puts("root@container:/#\n");
    } else if (strcmp(args[1], "build") == 0) {
        vga_puts("Step 1/5 : FROM ubuntu:22.04\n");
        vga_puts("Step 2/5 : RUN apt-get update\n");
        vga_puts("Step 3/5 : COPY . /app\n");
        vga_puts("Step 4/5 : WORKDIR /app\n");
        vga_puts("Step 5/5 : CMD [\"./app\"]\n");
        vga_puts("Successfully built a1b2c3d4e5f6\n");
    } else {
        vga_puts("docker: '"); vga_puts(args[1]); vga_puts("' is not a docker command.\n");
    }
}

/* podman - container runtime */
static void cmd_podman(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: podman [ps|images|run|stop|rm|pull|push]\n");
        return;
    }
    if (strcmp(args[1], "ps") == 0) {
        vga_puts("CONTAINER ID  IMAGE          STATUS       NAMES\n");
        vga_puts("f6a1b2c3d4e5  nginx:latest   Up 2 hours   web\n");
    } else if (strcmp(args[1], "images") == 0) {
        vga_puts("REPOSITORY   TAG     IMAGE ID       SIZE\n");
        vga_puts("nginx        latest  f6a1b2c3d4e5   187MB\n");
    } else {
        vga_puts("podman: '"); vga_puts(args[1]); vga_puts("' is not a podman command.\n");
    }
}

/* kubectl - kubernetes CLI */
static void cmd_kubectl(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: kubectl [get|describe|create|delete|apply|logs|exec]\n");
        return;
    }
    if (strcmp(args[1], "get") == 0 && argc > 2) {
        if (strcmp(args[2], "pods") == 0) {
            vga_puts("NAME                    READY   STATUS    RESTARTS   AGE\n");
            vga_puts("nginx-7c5ddbdf54-abc12   1/1     Running   0          2h\n");
            vga_puts("redis-6f7b8c9d0-def34    1/1     Running   0          3h\n");
        } else if (strcmp(args[2], "services") == 0 || strcmp(args[2], "svc") == 0) {
            vga_puts("NAME         TYPE        CLUSTER-IP     PORT(S)   AGE\n");
            vga_puts("kubernetes   ClusterIP   10.96.0.1      443/TCP   1d\n");
            vga_puts("nginx        NodePort    10.96.100.20   80/TCP    2h\n");
        } else if (strcmp(args[2], "nodes") == 0) {
            vga_puts("NAME       STATUS   ROLES           AGE   VERSION\n");
            vga_puts("node1      Ready    control-plane   1d    v1.28.0\n");
            vga_puts("node2      Ready    <none>          1d    v1.28.0\n");
        } else if (strcmp(args[2], "deployments") == 0 || strcmp(args[2], "deploy") == 0) {
            vga_puts("NAME    READY   UP-TO-DATE   AVAILABLE   AGE\n");
            vga_puts("nginx   1/1     1            1           2h\n");
        }
    } else if (strcmp(args[1], "describe") == 0) {
        vga_puts("Name:             nginx\n");
        vga_puts("Namespace:        default\n");
        vga_puts("Status:           Running\n");
        vga_puts("Replicas:         1 desired, 1 updated, 1 total\n");
    } else if (strcmp(args[1], "logs") == 0) {
        vga_puts("2026-07-09T00:00:00Z [nginx] Starting...\n");
        vga_puts("2026-07-09T00:00:01Z [nginx] Listening on :80\n");
    } else if (strcmp(args[1], "apply") == 0) {
        vga_puts("resource configured\n");
    } else if (strcmp(args[1], "delete") == 0) {
        vga_puts("resource deleted\n");
    } else {
        vga_puts("kubectl: unknown command '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* aws - Amazon Web Services CLI */
static void cmd_aws(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: aws [ec2|s3|iam|lambda|ecs|cloudformation]\n");
        return;
    }
    if (strcmp(args[1], "ec2") == 0 && argc > 2 && strcmp(args[2], "describe-instances") == 0) {
        vga_puts("RESERVATIONS\n");
        vga_puts("  INSTANCES\n");
        vga_puts("    InstanceId: i-0123456789abcdef0\n");
        vga_puts("    InstanceType: t3.micro\n");
        vga_puts("    State: running\n");
        vga_puts("    PrivateIpAddress: 10.0.1.100\n");
    } else if (strcmp(args[1], "s3") == 0 && argc > 2 && strcmp(args[2], "ls") == 0) {
        vga_puts("2026-07-01 00:00:00 my-bucket\n");
        vga_puts("2026-06-15 00:00:00 backup-bucket\n");
    } else if (strcmp(args[1], "iam") == 0) {
        vga_puts("UserId:  AIDAXXXXXXXXXXXXXXXXX\n");
        vga_puts("Account: 123456789012\n");
        vga_puts("Arn:     arn:aws:iam::123456789012:user/admin\n");
    } else {
        vga_puts("aws: '"); vga_puts(args[1]); vga_puts("' is not a recognized command.\n");
    }
}

/* gcloud - Google Cloud CLI */
static void cmd_gcloud(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: gcloud [compute|container|sql|functions|run]\n");
        return;
    }
    if (strcmp(args[1], "compute") == 0 && argc > 2 && strcmp(args[2], "instances list") == 0) {
        vga_puts("NAME          ZONE           MACHINE_TYPE   STATUS\n");
        vga_puts("instance-1    us-central1-a  n1-standard-1  RUNNING\n");
    } else if (strcmp(args[1], "container") == 0 && argc > 2 && strcmp(args[2], "clusters list") == 0) {
        vga_puts("NAME       LOCATION     MASTER_VERSION  STATUS\n");
        vga_puts("my-cluster us-central1  1.28.3-gke.1200  RUNNING\n");
    } else {
        vga_puts("gcloud: '"); vga_puts(args[1]); vga_puts("' is not a gcloud command.\n");
    }
}

/* az - Azure CLI */
static void cmd_az(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: az [vm|network|storage|account|aks]\n");
        return;
    }
    if (strcmp(args[1], "vm") == 0 && argc > 2 && strcmp(args[2], "list") == 0) {
        vga_puts("Name            ResourceGroup    Location    Status\n");
        vga_puts("myVM            myRG             eastus      Running\n");
    } else if (strcmp(args[1], "aks") == 0 && argc > 2 && strcmp(args[2], "list") == 0) {
        vga_puts("Name            ResourceGroup    Location    NodeCount\n");
        vga_puts("myAKS           myRG             eastus      3\n");
    } else {
        vga_puts("az: '"); vga_puts(args[1]); vga_puts("' is not a recognized command.\n");
    }
}

/* terraform - infrastructure as code */
static void cmd_terraform(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: terraform [init|plan|apply|destroy|state]\n");
        return;
    }
    if (strcmp(args[1], "init") == 0) {
        vga_puts("Initializing the backend...\n");
        vga_puts("Initializing provider plugins...\n");
        vga_puts("Terraform has been successfully initialized!\n");
    } else if (strcmp(args[1], "plan") == 0) {
        vga_puts("Terraform will perform the following actions:\n\n");
        vga_puts("  + aws_instance.web\n");
        vga_puts("      + instance_type = \"t3.micro\"\n");
        vga_puts("      + ami           = \"ami-0123456789abcdef0\"\n");
        vga_puts("\nPlan: 1 to add, 0 to change, 0 to destroy.\n");
    } else if (strcmp(args[1], "apply") == 0) {
        vga_puts("Apply complete! Resources: 1 added, 0 changed, 0 destroyed.\n");
    } else if (strcmp(args[1], "destroy") == 0) {
        vga_puts("Destroy complete! Resources: 1 destroyed.\n");
    } else {
        vga_puts("terraform: '"); vga_puts(args[1]); vga_puts("' is not a terraform command.\n");
    }
}

/* ansible - configuration management */
static void cmd_ansible(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: ansible [playbook|inventory|vault|galaxy]\n");
        return;
    }
    if (strcmp(args[1], "playbook") == 0) {
        vga_puts("PLAY [deploy] *******************************************\n");
        vga_puts("TASK [Gathering Facts] **********************************\n");
        vga_puts("ok: [server1]\n");
        vga_puts("TASK [Install nginx] ************************************\n");
        vga_puts("changed: [server1]\n");
        vga_puts("PLAY RECAP **********************************************\n");
        vga_puts("server1: ok=2 changed=1 unreachable=0 failed=0\n");
    } else if (strcmp(args[1], "inventory") == 0) {
        vga_puts("[webservers]\n");
        vga_puts("server1 ansible_host=10.0.1.10\n");
        vga_puts("server2 ansible_host=10.0.1.11\n");
        vga_puts("\n[dbservers]\n");
        vga_puts("db1 ansible_host=10.0.2.10\n");
    } else {
        vga_puts("ansible: '"); vga_puts(args[1]); vga_puts("' is not an ansible command.\n");
    }
}

/* mysql - MySQL client */
static void cmd_mysql(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: mysql [-u user] [-p] [database]\n");
        vga_puts("Welcome to MySQL monitor.\n");
        return;
    }
    if (strcmp(args[1], "--version") == 0 || strcmp(args[1], "-V") == 0) {
        vga_puts("mysql  Ver 8.0.36 for Linux (x86_64)\n");
    } else if (strcmp(args[1], "-e") == 0 && argc > 2) {
        vga_puts("+----+--------+--------+\n");
        vga_puts("| id | name   | email  |\n");
        vga_puts("+----+--------+--------+\n");
        vga_puts("|  1 | admin  | a@b.c  |\n");
        vga_puts("|  2 | user1  | u@b.c  |\n");
        vga_puts("+----+--------+--------+\n");
    } else {
        vga_puts("mysql> Type 'help' for help.\n");
        vga_puts("mysql> \n");
    }
}

/* psql - PostgreSQL client */
static void cmd_psql(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: psql [-U user] [-d database]\n");
        vga_puts("psql (15.4)\n");
        return;
    }
    if (strcmp(args[1], "--version") == 0) {
        vga_puts("psql (PostgreSQL) 15.4\n");
    } else if (strcmp(args[1], "-c") == 0 && argc > 2) {
        vga_puts(" id | name  | email \n----+-------+--------\n");
        vga_puts("  1 | admin | a@b.c\n");
        vga_puts("  2 | user1 | u@b.c\n");
        vga_puts("(2 rows)\n");
    } else {
        vga_puts("psql (15.4)\n");
        vga_puts("Type \"help\" for help.\n");
    }
}

/* redis-cli - Redis client */
static void cmd_redis_cli(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("redis-cli 7.2.3\n");
        vga_puts("Type \"help\" for help.\n");
        return;
    }
    if (strcmp(args[1], "ping") == 0) {
        vga_puts("PONG\n");
    } else if (strcmp(args[1], "info") == 0) {
        vga_puts("# Server\n");
        vga_puts("redis_version:7.2.3\n");
        vga_puts("uptime_in_seconds:86400\n");
        vga_puts("# Memory\n");
        vga_puts("used_memory:1234567\n");
        vga_puts("used_memory_human:1.18M\n");
    } else if (strcmp(args[1], "keys") == 0) {
        vga_puts("1) \"session:abc123\"\n");
        vga_puts("2) \"user:1\"\n");
        vga_puts("3) \"config:app\"\n");
    } else if (strcmp(args[1], "get") == 0 && argc > 2) {
        vga_puts("\"value\"\n");
    } else if (strcmp(args[1], "set") == 0 && argc > 3) {
        vga_puts("OK\n");
    } else {
        vga_puts("redis> \n");
    }
}

/* nginx - web server */
static void cmd_nginx(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: nginx [-t|-s|-v|-V|start|stop|reload|status]\n");
        return;
    }
    if (strcmp(args[1], "-v") == 0) {
        vga_puts("nginx version: nginx/1.24.0\n");
    } else if (strcmp(args[1], "-t") == 0) {
        vga_puts("nginx: the configuration file /etc/nginx/nginx.conf syntax is ok\n");
        vga_puts("nginx: configuration file /etc/nginx/nginx.conf test is successful\n");
    } else if (strcmp(args[1], "start") == 0 || strcmp(args[1], "-s") == 0) {
        vga_puts("nginx started\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_puts("nginx stopped\n");
    } else if (strcmp(args[1], "reload") == 0) {
        vga_puts("nginx: configuration file reloaded\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_puts("Active connections: 25\n");
        vga_puts("server accepts handled requests\n");
        vga_puts(" 123 123 456\n");
        vga_puts("Reading: 0 Writing: 5 Waiting: 20\n");
    } else {
        vga_puts("nginx: '"); vga_puts(args[1]); vga_puts("' is not a valid option.\n");
    }
}

/* httpd - Apache web server */
static void cmd_httpd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: httpd [-k start|stop|restart|-v|-t]\n");
        return;
    }
    if (strcmp(args[1], "-v") == 0) {
        vga_puts("Server version: Apache/2.4.58 (Unix)\n");
    } else if (strcmp(args[1], "-t") == 0) {
        vga_puts("Syntax OK\n");
    } else if (strcmp(args[1], "-k") == 0 && argc > 2) {
        if (strcmp(args[2], "start") == 0) vga_puts("Apache started\n");
        else if (strcmp(args[2], "stop") == 0) vga_puts("Apache stopped\n");
        else if (strcmp(args[2], "restart") == 0) vga_puts("Apache restarted\n");
    } else {
        vga_puts("httpd: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* caddy - web server */
static void cmd_caddy(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: caddy [start|stop|reload|validate|version]\n");
        return;
    }
    if (strcmp(args[1], "version") == 0) {
        vga_puts("v2.7.6 h1:813682196\n");
    } else if (strcmp(args[1], "validate") == 0) {
        vga_puts("Valid configuration\n");
    } else if (strcmp(args[1], "start") == 0) {
        vga_puts("caddy started\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_puts("caddy stopped\n");
    } else {
        vga_puts("caddy: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* php - PHP interpreter */
static void cmd_php(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("PHP 8.2.12 (cli)\n");
        vga_puts("Usage: php [file|?r code|?m|?v|?i]\n");
        return;
    }
    if (strcmp(args[1], "-v") == 0) {
        vga_puts("PHP 8.2.12 (cli) (NTS)\n");
    } else if (strcmp(args[1], "-m") == 0) {
        vga_puts("[Core]\n[Date]\n[Filter]\n[Hash]\n[Json]\n[Mbstring]\n[PDO]\n[Session]\n");
    } else if (strcmp(args[1], "-i") == 0) {
        vga_puts("phpinfo()\nPHP Version => 8.2.12\nSystem => Linux BYO-OS\n");
    } else {
        vga_puts("PHP 8.2.12\n");
    }
}

/* composer - PHP package manager */
static void cmd_composer(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Composer version 2.6.5\n");
        vga_puts("Usage: composer [install|update|require|dump-autoload]\n");
        return;
    }
    if (strcmp(args[1], "install") == 0) {
        vga_puts("Installing dependencies...\n");
        vga_puts("Package operations: 5 installs, 0 updates, 0 removals\n");
        vga_puts("  - Installing vendor/package (v1.0.0)\n");
        vga_puts("Generating autoload files\n");
    } else if (strcmp(args[1], "update") == 0) {
        vga_puts("Loading composer repositories\n");
        vga_puts("Updating dependencies\n");
        vga_puts("Nothing to install or update\n");
    } else {
        vga_puts("composer: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* bundler - Ruby package manager */
static void cmd_bundler(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Bundler version 2.4.22\n");
        vga_puts("Usage: bundle [install|update|exec|exec]\n");
        return;
    }
    if (strcmp(args[1], "install") == 0) {
        vga_puts("Fetching gem metadata...\n");
        vga_puts("Installing rake 13.1.0\n");
        vga_puts("Bundle complete!\n");
    } else {
        vga_puts("bundle: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* pip - Python package manager */
static void cmd_pip(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("pip 23.3.1\n");
        vga_puts("Usage: pip [install|list|show|freeze|uninstall]\n");
        return;
    }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("Package    Version\n");
        vga_puts("---------- -------\n");
        vga_puts("flask      3.0.0\n");
        vga_puts("requests   2.31.0\n");
        vga_puts("numpy      1.26.2\n");
    } else if (strcmp(args[1], "install") == 0 && argc > 2) {
        vga_puts("Collecting "); vga_puts(args[2]); vga_puts("\n");
        vga_puts("Installing collected packages: "); vga_puts(args[2]); vga_puts("\n");
        vga_puts("Successfully installed "); vga_puts(args[2]); vga_puts("\n");
    } else if (strcmp(args[1], "freeze") == 0) {
        vga_puts("flask==3.0.0\nrequests==2.31.0\nnumpy==1.26.2\n");
    } else {
        vga_puts("pip: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* cargo - Rust package manager */
static void cmd_cargo(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("cargo 1.74.0\n");
        vga_puts("Usage: cargo [build|run|test|check|clippy|fmt|new|init]\n");
        return;
    }
    if (strcmp(args[1], "build") == 0) {
        vga_puts("   Compiling myproject v0.1.0\n");
        vga_puts("    Finished dev [unoptimized + debuginfo] target(s)\n");
    } else if (strcmp(args[1], "run") == 0) {
        vga_puts("   Compiling myproject v0.1.0\n");
        vga_puts("    Finished dev [unoptimized + debuginfo] target(s)\n");
        vga_puts("     Running target/debug/myproject\n");
        vga_puts("Hello, world!\n");
    } else if (strcmp(args[1], "test") == 0) {
        vga_puts("   Compiling myproject v0.1.0\n");
        vga_puts("    Finished test [unoptimized + debuginfo] target(s)\n");
        vga_puts("     Running unittests\n");
        vga_puts("test result: ok. 3 passed; 0 failed\n");
    } else {
        vga_puts("cargo: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* go - Go compiler */
static void cmd_go(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("go version go1.21.5 linux/386\n");
        vga_puts("Usage: go [build|run|test|fmt|get|mod|vet]\n");
        return;
    }
    if (strcmp(args[1], "version") == 0) {
        vga_puts("go version go1.21.5 linux/386\n");
    } else if (strcmp(args[1], "build") == 0) {
        vga_puts("Build successful.\n");
    } else if (strcmp(args[1], "test") == 0) {
        vga_puts("ok  \tmyproject\t0.003s\n");
    } else if (strcmp(args[1], "run") == 0) {
        vga_puts("Hello, world!\n");
    } else {
        vga_puts("go: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* npm - Node.js package manager */
static void cmd_npm(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("npm 10.2.3\n");
        vga_puts("Usage: npm [install|init|start|test|run|update|ls|outdated]\n");
        return;
    }
    if (strcmp(args[1], "install") == 0 && argc > 2) {
        vga_puts("added 1 package in 2s\n");
        vga_puts("\n1 package is looking for funding\n");
    } else if (strcmp(args[1], "ls") == 0) {
        vga_puts("myproject@1.0.0\n");
        vga_puts("+-- express@4.18.2\n");
        vga_puts("+-- lodash@4.17.21\n");
        vga_puts("+-- axios@1.6.2\n");
    } else if (strcmp(args[1], "outdated") == 0) {
        vga_puts("Package  Current  Wanted  Latest\n");
        vga_puts("express   4.18.2   4.18.2   4.19.0\n");
    } else if (strcmp(args[1], "init") == 0) {
        vga_puts("Wrote to /package.json\n");
    } else {
        vga_puts("npm: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* yarn - Node.js package manager */
static void cmd_yarn(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("yarn v1.22.21\n");
        vga_puts("Usage: yarn [add|remove|install|list|upgrade|init]\n");
        return;
    }
    if (strcmp(args[1], "install") == 0) {
        vga_puts("[1/4] Resolving packages...\n");
        vga_puts("[2/4] Fetching packages...\n");
        vga_puts("[3/4] Linking dependencies...\n");
        vga_puts("[4/4] Building fresh packages...\n");
        vga_puts("success Saved lockfile.\n");
    } else {
        vga_puts("yarn: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* npx - Node.js package runner */
static void cmd_npx(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: npx <package> [args...]\n");
        return;
    }
    vga_puts("npx: installed 1 in 2s\n");
    vga_puts("Hello from "); vga_puts(args[1]); vga_puts("!\n");
}

/* jenkins - CI/CD server */
static void cmd_jenkins(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: jenkins [start|stop|restart|status]\n");
        return;
    }
    if (strcmp(args[1], "start") == 0) {
        vga_puts("Jenkins started on http://localhost:8080\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_puts("Jenkins stopped\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_puts("Jenkins is running (pid 12345)\n");
        vga_puts("URL: http://localhost:8080\n");
    } else {
        vga_puts("jenkins: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* gitlab-ci - GitLab CI */
static void cmd_gitlab_ci(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("GitLab CI/CD Runner v16.6.0\n");
    vga_puts("Usage: gitlab-ci [register|run|list]\n");
}

/* prometheus - monitoring */
static void cmd_prometheus(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: prometheus [--config.file|--web.listen-address]\n");
        return;
    }
    if (strcmp(args[1], "--version") == 0 || strcmp(args[1], "-v") == 0) {
        vga_puts("prometheus, version 2.48.0\n");
    } else {
        vga_puts("prometheus: started on :9090\n");
    }
}

/* grafana - dashboards */
static void cmd_grafana(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: grafana [server|cli|version]\n");
        return;
    }
    if (strcmp(args[1], "version") == 0) {
        vga_puts("Grafana v10.2.2\n");
    } else if (strcmp(args[1], "server") == 0) {
        vga_puts("Grafana server starting on http://localhost:3000\n");
    } else {
        vga_puts("grafana: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* nagios - monitoring */
static void cmd_nagios(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: nagios [start|stop|restart|status]\n");
        return;
    }
    if (strcmp(args[1], "start") == 0) {
        vga_puts("Nagios started on http://localhost/nagios/\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_puts("Nagios is running\n");
        vga_puts("Hosts: 5 up, 0 down\n");
        vga_puts("Services: 25 ok, 2 warning, 0 critical\n");
    } else {
        vga_puts("nagios: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* zabbix - monitoring */
static void cmd_zabbix(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: zabbix_agentd [-c config|-V|-h]\n");
        return;
    }
    if (strcmp(args[1], "-V") == 0 || strcmp(args[1], "--version") == 0) {
        vga_puts("Zabbix agent daemon v6.4.8\n");
    } else {
        vga_puts("zabbix: started\n");
    }
}

/* elasticsearch - search engine */
static void cmd_elasticsearch(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: elasticsearch [-E setting=value]\n");
        return;
    }
    vga_puts("elasticsearch: started on :9200\n");
}

/* logstash - log pipeline */
static void cmd_logstash(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: logstash [-f config]\n");
        return;
    }
    vga_puts("logstash: pipeline started\n");
}

/* kibana - visualization */
static void cmd_kibana(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: kibana [--port]\n");
        return;
    }
    vga_puts("kibana: listening on :5601\n");
}

/* rabbitmq - message queue */
static void cmd_rabbitmq(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: rabbitmqctl [status|list_queues|add_user]\n");
        return;
    }
    if (strcmp(args[1], "status") == 0) {
        vga_puts("Status of node rabbit@localhost\n");
        vga_puts("Queues: 5 total, 0 messages\n");
        vga_puts("Connections: 3\n");
        vga_puts("Channels: 5\n");
    } else if (strcmp(args[1], "list_queues") == 0) {
        vga_puts("Timeout: 60.0\n");
        vga_puts("Listing queues\n");
        vga_puts("name\tmessages\n");
        vga_puts("orders\t0\n");
        vga_puts("notifications\t0\n");
    } else {
        vga_puts("rabbitmqctl: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* kafka - event streaming */
static void cmd_kafka(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: kafka [console-producer|console-consumer|topics]\n");
        return;
    }
    if (strcmp(args[1], "topics") == 0 && argc > 2 && strcmp(args[2], "--list") == 0) {
        vga_puts("orders\nnotifications\nlogs\n");
    } else {
        vga_puts("kafka: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* minio - S3-compatible storage */
static void cmd_minio(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: minio [server|client]\n");
        return;
    }
    if (strcmp(args[1], "server") == 0) {
        vga_puts("MinIO started on http://localhost:9000\n");
        vga_puts("API: http://localhost:9000\n");
        vga_puts("Console: http://localhost:9001\n");
    } else {
        vga_puts("minio: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* vault - secrets management */
static void cmd_vault(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: vault [server|status|read|write|kv]\n");
        return;
    }
    if (strcmp(args[1], "status") == 0) {
        vga_puts("Key             Value\n");
        vga_puts("---             -----\n");
        vga_puts("Seal Type       shamir\n");
        vga_puts("Initialized     true\n");
        vga_puts("Sealed          false\n");
        vga_puts("Version         1.15.4\n");
    } else {
        vga_puts("vault: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* consul - service discovery */
static void cmd_consul(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: consul [agent|members|services|kv]\n");
        return;
    }
    if (strcmp(args[1], "members") == 0) {
        vga_puts("Node    Address        Status  Build\n");
        vga_puts("server1 10.0.1.10:8301  alive   1.15.4\n");
        vga_puts("server2 10.0.1.11:8301  alive   1.15.4\n");
    } else if (strcmp(args[1], "services") == 0) {
        vga_puts("consul: 1\n");
        vga_puts("web: 1\n");
        vga_puts("api: 1\n");
    } else {
        vga_puts("consul: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}
