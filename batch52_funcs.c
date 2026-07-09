/* ===== Batch 52: Database + Container + DevOps ===== */
static void cmd_mariadb52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: mariadb <connect|query|show|status|dump>\n");return;}
    if(strcmp(args[1],"connect")==0){vga_puts("Connecting to MariaDB 10.11.2 at 127.0.0.1:3306...\n");vga_puts("Welcome to MariaDB 10.11.2\n");}
    else if(strcmp(args[1],"query")==0){if(argc<3){vga_puts("Usage: mariadb query <sql>\n");return;}vga_puts("Query: ");vga_puts(args[2]);vga_putchar('\n');vga_puts("| id | name   | email             |\n|  1 | alice  | alice@example.com |\n|  2 | bob    | bob@example.com   |\n2 rows in set\n");}
    else if(strcmp(args[1],"show")==0){vga_puts("| Database           |\n| information_schema |\n| byo_os             |\n| mysql              |\n");}
    else if(strcmp(args[1],"status")==0){vga_puts("MariaDB: Connected\nServer: localhost:3306\nVersion: 10.11.2\n");}
    else if(strcmp(args[1],"dump")==0){vga_puts("-- MariaDB dump 10.11\nCREATE DATABASE byo_os;\nCREATE TABLE users(id INT, name VARCHAR(64));\n");} else { vga_puts("mariadb: unknown command\n"); }
}
static void cmd_cassandra52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: cassandra <connect|query|describe|status|nodetool>\n");return;}
    if(strcmp(args[1],"connect")==0){vga_puts("Datacenter: datacenter1\nRack: rack1\nVersion: 4.1.3\nStatus: UN (Up/Normal)\n");}
    else if(strcmp(args[1],"query")==0){if(argc<3){vga_puts("Usage: cassandra query <cql>\n");return;}vga_puts("CQL: ");vga_puts(args[2]);vga_putchar('\n');vga_puts("id | name  | data\n---+-------+-----\n1001 | alice | ...\n1002 | bob   | ...\n");}
    else if(strcmp(args[1],"describe")==0){vga_puts("Keyspace: byo_os\n  Replication: SimpleStrategy, RF=3\n  Table: users\n    Columns: id (int PK), name (text)\n");}
    else if(strcmp(args[1],"status")==0){vga_puts("Datacenter: datacenter1\nStatus=UN  Nodes: 3\nLoad: 256.0 MB\n");}
    else if(strcmp(args[1],"nodetool")==0){vga_puts("nodetool info\n  Cluster: BYO-Cluster\n  Status: Normal\n  Heap: 256MB/1024MB\n");} else { vga_puts("cassandra: unknown command\n"); }
}
static void cmd_elasticsearch52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: elasticsearch <status|search|index|cluster|indices>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("Cluster: byo-cluster (green)\n  Nodes: 3  Shards: 12\n  Documents: 4219\n");}
    else if(strcmp(args[1],"search")==0){if(argc<3){vga_puts("Usage: elasticsearch search <query>\n");return;}vga_puts("GET /_search?q=");vga_puts(args[2]);vga_putchar('\n');vga_puts("  hits.total: 42\n  hits[0]: {_index:logs,_id:1}\n");}
    else if(strcmp(args[1],"index")==0){vga_puts("PUT /byo_os/_doc/1\nAcknowledged: true\n");}
    else if(strcmp(args[1],"cluster")==0){vga_puts("Cluster: byo-cluster (green)\n  Version: 8.11.1\n  Nodes: 3  Indices: 5\n");}
    else if(strcmp(args[1],"indices")==0){vga_puts("green  open logs    1 1  2847  1.2mb\ngreen  open users   1 1  1372  512kb\n");} else { vga_puts("elasticsearch: unknown command\n"); }
}
static void cmd_couchdb52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: couchdb <status|databases|put|get|replicate>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("CouchDB 3.3.2\n  Single node\n  Uptime: 5d 12h\n");}
    else if(strcmp(args[1],"databases")==0){vga_puts("[\"_users\",\"byo_config\",\"byo_logs\",\"sessions\"]\n");}
    else if(strcmp(args[1],"put")==0){if(argc<3){vga_puts("Usage: couchdb put <doc>\n");return;}vga_puts("PUT /byo_config/");vga_puts(args[2]);vga_putchar('\n');vga_puts("  {\"ok\":true,\"rev\":\"1-abc\"}\n");}
    else if(strcmp(args[1],"get")==0){if(argc<3){vga_puts("Usage: couchdb get <id>\n");return;}vga_puts("GET /byo_config/");vga_puts(args[2]);vga_putchar('\n');vga_puts("  {\"ok\":true,\"value\":\"data\"}\n");}
    else if(strcmp(args[1],"replicate")==0){vga_puts("Replicating source->target\n  Status: completed\n  Docs: 42/42\n");} else { vga_puts("couchdb: unknown command\n"); }
}
static void cmd_influxdb52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: influxdb <version|query|write|buckets|ping>\n");return;}
    if(strcmp(args[1],"version")==0){vga_puts("InfluxDB v2.7.1\n  Build: 2023-12-08\n");}
    else if(strcmp(args[1],"query")==0){if(argc<3){vga_puts("Usage: influxdb query <flux>\n");return;}vga_puts("Flux: ");vga_puts(args[2]);vga_putchar('\n');vga_puts("time                  value\n2024-01-15T12:00:00Z  42.5\n2024-01-15T12:01:00Z  43.1\n");}
    else if(strcmp(args[1],"write")==0){vga_puts("Write: cpu,host=byo value=42.5\n  Points: 1\n  Status: 204\n");}
    else if(strcmp(args[1],"buckets")==0){vga_puts("Name         Retention  Type\nmetrics      30d        bucket\nsensor_data  7d         bucket\nlogs         90d        bucket\n");}
    else if(strcmp(args[1],"ping")==0){vga_puts("InfluxDB alive: 200 OK\n");} else { vga_puts("influxdb: unknown command\n"); }
}
static void cmd_neo4j52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: neo4j <status|cypher|schema|import|console>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("Neo4j 5.14.0\n  Bolt: bolt://localhost:7687\n  HTTP: http://localhost:7474\n  State: ONLINE\n");}
    else if(strcmp(args[1],"cypher")==0){if(argc<3){vga_puts("Usage: neo4j cypher <query>\n");return;}vga_puts("Cypher: ");vga_puts(args[2]);vga_putchar('\n');vga_puts("|  id  | name  |\n|    1 | Alice |\n|    2 | Bob   |\n2 rows\n");}
    else if(strcmp(args[1],"schema")==0){vga_puts("Indexes:\n  (:Person {id})    UNIQUE  READY\n  (:Person {name})  RANGE   READY\n");}
    else if(strcmp(args[1],"import")==0){vga_puts("Importing graph...\n  Nodes: 128  Relationships: 256\n  Done in 2.3s\n");}
    else if(strcmp(args[1],"console")==0){vga_puts("Neo4j Browser: http://localhost:7474\n");} else { vga_puts("neo4j: unknown command\n"); }
}
static void cmd_memcached52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: memcached <status|stats|set|get|flush>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("Memcached 1.6.21\n  Port: 11211\n  Max connections: 1024\n  Memory: 64MB\n");}
    else if(strcmp(args[1],"stats")==0){vga_puts("STAT pid 1234\nSTAT curr_connections 12\nSTAT cmd_get 4521\nSTAT cmd_set 2847\nSTAT get_hits 4102\nSTAT get_misses 419\nEND\n");}
    else if(strcmp(args[1],"set")==0){if(argc<4){vga_puts("Usage: memcached set <key> <value>\n");return;}vga_puts("STORED ");vga_puts(args[2]);vga_putchar('\n');}
    else if(strcmp(args[1],"get")==0){if(argc<3){vga_puts("Usage: memcached get <key>\n");return;}vga_puts("VALUE ");vga_puts(args[2]);vga_puts(" 0 5\ndata1\nEND\n");}
    else if(strcmp(args[1],"flush")==0){vga_puts("OK\n");} else { vga_puts("memcached: unknown command\n"); }
}
static void cmd_rabbitmq52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: rabbitmq <status|queues|publish|consume|users>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("RabbitMQ 3.12.12\n  Node: rabbit@byo-os\n  Messages: 1247\n  Connections: 8  Queues: 4\n");}
    else if(strcmp(args[1],"queues")==0){vga_puts("  Name               Msgs  Consumers\n  orders               1247        3\n  notifications         42        1\n  logs                8192        0\n");}
    else if(strcmp(args[1],"publish")==0){if(argc<4){vga_puts("Usage: rabbitmq publish <queue> <msg>\n");return;}vga_puts("Publishing to ");vga_puts(args[2]);vga_putchar('\n');vga_puts("Message published (delivery-tag: 1)\n");}
    else if(strcmp(args[1],"consume")==0){if(argc<3){vga_puts("Usage: rabbitmq consume <queue>\n");return;}vga_puts("Consuming from ");vga_puts(args[2]);vga_putchar('\n');vga_puts("  {\"id\":1,\"type\":\"order\"}\n  [basic.ack]\n");}
    else if(strcmp(args[1],"users")==0){vga_puts("  guest  admin  [ ]\n  admin  admin  [ ]\n");} else { vga_puts("rabbitmq: unknown command\n"); }
}
static void cmd_kafka52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: kafka <status|topics|produce|consume|groups>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("Kafka 3.6.1\n  Cluster: byo-kafka\n  Brokers: 3\n  Partitions: 12\n");}
    else if(strcmp(args[1],"topics")==0){vga_puts("  Name         Partitions  Replicas\n  events           6          3\n  metrics          3          3\n  audit-logs       9          3\n");}
    else if(strcmp(args[1],"produce")==0){if(argc<4){vga_puts("Usage: kafka produce <topic> <msg>\n");return;}vga_puts("Producing to ");vga_puts(args[2]);vga_putchar('\n');vga_puts("  Offset: 12847  Partition: 2\n");}
    else if(strcmp(args[1],"consume")==0){if(argc<3){vga_puts("Usage: kafka consume <topic>\n");return;}vga_puts("Consuming from ");vga_puts(args[2]);vga_putchar('\n');vga_puts("  {\"id\":1,\"event\":\"click\"}\n  {\"id\":2,\"event\":\"view\"}\n");}
    else if(strcmp(args[1],"groups")==0){vga_puts("  Group          State    Members  Lag\n  web-service    Stable     3       42\n  analytics       Stable     2      128\n");} else { vga_puts("kafka: unknown command\n"); }
}
static void cmd_nats52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: nats <status|pub|sub|streams|accounts>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("NATS 2.10.9\n  Cluster: byo-nats\n  Nodes: 3  Connections: 24\n  Subscriptions: 156\n");}
    else if(strcmp(args[1],"pub")==0){if(argc<4){vga_puts("Usage: nats pub <subject> <msg>\n");return;}vga_puts("Published to ");vga_puts(args[2]);vga_puts(": ");vga_puts(args[3]);vga_putchar('\n');}
    else if(strcmp(args[1],"sub")==0){if(argc<3){vga_puts("Usage: nats sub <subject>\n");return;}vga_puts("Subscribed to ");vga_puts(args[2]);vga_putchar('\n');vga_puts("  [orders.new] {\"id\":1}\n  [orders.new] {\"id\":2}\n");}
    else if(strcmp(args[1],"streams")==0){vga_puts("  Name       Subjects    Storage  Msgs\n  ORDERS     orders.*    File     1247\n  EVENTS     events.>    Memory    842\n");}
    else if(strcmp(args[1],"accounts")==0){vga_puts("  SYS     Conn:3   Subs:12\n  APP     Conn:12  Subs:84\n");} else { vga_puts("nats: unknown command\n"); }
}
static void cmd_podman52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: podman <ps|images|run|pull|build|logs|stop|rm>\n");return;}
    if(strcmp(args[1],"ps")==0){vga_puts("CONTAINER ID  IMAGE               STATUS      NAMES\n  a1b2c3d4e5f6  nginx:alpine        Up 2h       web-server\n  f6e5d4c3b2a1  redis:7             Up 1d       cache\n");}
    else if(strcmp(args[1],"images")==0){vga_puts("REPOSITORY    TAG    IMAGE ID       SIZE\n  nginx         alpine a1b2c3d4e5f6   42MB\n  redis         7      f6e5d4c3b2a1   32MB\n  postgres      16     1a2b3c4d5e6f   156MB\n");}
    else if(strcmp(args[1],"run")==0){if(argc<3){vga_puts("Usage: podman run <image>\n");return;}vga_puts("Running ");vga_puts(args[2]);vga_puts("...\n  Container: 9f8e7d6c5b4a\n  Port: 8080->80\n");}
    else if(strcmp(args[1],"pull")==0){if(argc<3){vga_puts("Usage: podman pull <image>\n");return;}vga_puts("Pulling ");vga_puts(args[2]);vga_puts("...\n  Downloaded\n");}
    else if(strcmp(args[1],"build")==0){vga_puts("Building from Containerfile...\n  Step 1/4: FROM alpine\n  Step 2/4: RUN apk add nginx\n  Step 3/4: COPY nginx.conf /\n  Step 4/4: EXPOSE 80\n  Built: a1b2c3d4\n");}
    else if(strcmp(args[1],"logs")==0){vga_puts("[stdout] 12:00:00 Server started\n[stderr] 12:00:01 Connection\n");}
    else if(strcmp(args[1],"stop")==0){vga_puts("Container stopped\n");}
    else if(strcmp(args[1],"rm")==0){vga_puts("Container removed\n");} else { vga_puts("podman: unknown command\n"); }
}
static void cmd_buildah52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: buildah <images|containers|from|run|commit|rmi>\n");return;}
    if(strcmp(args[1],"images")==0){vga_puts("REPOSITORY    TAG    IMAGE ID       SIZE\n  nginx         alpine a1b2c3d4e5f6   42MB\n  python        3.11   b2c3d4e5f6a1   180MB\n");}
    else if(strcmp(args[1],"containers")==0){vga_puts("CONTAINER ID  IMAGE      NAMES\n  9f8e7d6c5b4a  alpine     working-container\n");}
    else if(strcmp(args[1],"from")==0){if(argc<3){vga_puts("Usage: buildah from <image>\n");return;}vga_puts("Working container \"");vga_puts(args[2]);vga_puts("\" created\n");}
    else if(strcmp(args[1],"run")==0){vga_puts("RUN: apk add --no-cache curl\n  Step 2/3: RUN curl http://example.com\n  Step 3/3: WORKDIR /app\n");}
    else if(strcmp(args[1],"commit")==0){vga_puts("COMMIT: sha256:c1d2e3f4\n  Image: myapp:latest\n  Size: 85MB\n");}
    else if(strcmp(args[1],"rmi")==0){vga_puts("Image removed\n");} else { vga_puts("buildah: unknown command\n"); }
}
static void cmd_skopeo52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: skopeo <inspect|copy|list-tags|delete>\n");return;}
    if(strcmp(args[1],"inspect")==0){vga_puts("Image: docker.io/library/nginx:alpine\n  Arch: amd64  OS: linux\n  Created: 2024-01-10\n  Layers: 5  Size: 42MB\n");}
    else if(strcmp(args[1],"copy")==0){vga_puts("Copying docker.io/library/nginx:alpine\n  -> registry.local:5000/nginx:alpine\n  Copied\n");}
    else if(strcmp(args[1],"list-tags")==0){vga_puts("Tags: alpine, 1.25.3, 1.25, mainline, latest\n");}
    else if(strcmp(args[1],"delete")==0){vga_puts("Image deleted\n");} else { vga_puts("skopeo: unknown command\n"); }
}
static void cmd_crictl52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: crictl <pods|ps|images|inspect|logs|pull>\n");return;}
    if(strcmp(args[1],"pods")==0){vga_puts("POD ID              STATE  NAME           NAMESPACE\n  abc123              Ready  web-pod-7x9k2  default\n  def456              Ready  redis-pod      default\n");}
    else if(strcmp(args[1],"ps")==0){vga_puts("CONTAINER ID  IMAGE           STATE    NAME\n  1a2b3c4d5e6f  nginx:alpine    Running  web-server\n  f6e5d4c3b2a1  redis:7         Running  cache\n");}
    else if(strcmp(args[1],"images")==0){vga_puts("IMAGE               TAG    SIZE\n  docker.io/library/nginx  alpine  42MB\n  docker.io/library/redis  7       32MB\n");}
    else if(strcmp(args[1],"inspect")==0){vga_puts("ID: 1a2b3c4d\n  Image: nginx:alpine\n  State: Running\n  Restart Count: 0\n");}
    else if(strcmp(args[1],"logs")==0){vga_puts("12:00:00 server listening on port 80\n12:00:01 connection accepted\n");}
    else if(strcmp(args[1],"pull")==0){if(argc<3){vga_puts("Usage: crictl pull <image>\n");return;}vga_puts("Pulling ");vga_puts(args[2]);vga_puts("... pulled\n");} else { vga_puts("crictl: unknown command\n"); }
}
static void cmd_kind52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: kind <create|delete|list|clusters|export|load>\n");return;}
    if(strcmp(args[1],"create")==0){vga_puts("Creating cluster \"kind\"...\n  K8s 1.28.3\n  kubeadm configured\n  CNI: calico\n  Ready!\n");}
    else if(strcmp(args[1],"delete")==0){vga_puts("Deleting cluster \"kind\"...\n  Nodes removed\n  Volumes cleaned\n  Deleted\n");}
    else if(strcmp(args[1],"list")==0){vga_puts("NAME                STATUS  ROLES    VERSION\n  kind-control-plane  Ready   master   v1.28.3\n");}
    else if(strcmp(args[1],"clusters")==0){vga_puts("kind-cluster\n  1 control-plane  K8s v1.28.3  Ready\n");}
    else if(strcmp(args[1],"export")==0){vga_puts("kubeconfig exported\n");}
    else if(strcmp(args[1],"load")==0){vga_puts("Image loaded into cluster\n");} else { vga_puts("kind: unknown command\n"); }
}
static void cmd_minikube52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: minikube <start|stop|status|dashboard|addons|config>\n");return;}
    if(strcmp(args[1],"start")==0){vga_puts("Starting minikube...\n  Driver: hyperv\n  K8s v1.28.3\n  Addons: storage-provisioner, default-storageclass\n  Done!\n");}
    else if(strcmp(args[1],"stop")==0){vga_puts("Stopping minikube...\n  Cluster stopped\n");}
    else if(strcmp(args[1],"status")==0){vga_puts("minikube\n  host: Running\n  kubelet: Running\n  apiserver: Running\n  kubectl: Configured\n");}
    else if(strcmp(args[1],"dashboard")==0){vga_puts("Opening dashboard at http://127.0.0.1:8001/\n");}
    else if(strcmp(args[1],"addons")==0){vga_puts("  dashboard         enabled\n  ingress           disabled\n  metrics-server    disabled\n  storage           enabled\n");}
    else if(strcmp(args[1],"config")==0){vga_puts("  cpus: 2\n  memory: 4096\n  driver: hyperv\n  k8s: v1.28.3\n");} else { vga_puts("minikube: unknown command\n"); }
}
static void cmd_k9s52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: k9s <pods|deploy|svc|ns|logs|tree>\n");return;}
    if(strcmp(args[1],"pods")==0){vga_puts("  K9s - Pod View\n  NAME                READY  STATUS   AGE\n  web-7d8f-x9k2l      1/1    Running  2d\n  redis-6a5b-m3n1p    1/1    Running  3d\n  api-8c7d-q1r2s      1/1    Running  1d\n");}
    else if(strcmp(args[1],"deploy")==0){vga_puts("  K9s - Deploy View\n  NAME    READY  UP-TO-DATE  AVAILABLE\n  web     3/3    3           3\n  redis   1/1    1           1\n  api     2/2    2           2\n");}
    else if(strcmp(args[1],"svc")==0){vga_puts("  NAME    TYPE       CLUSTER-IP    PORT(S)\n  web     ClusterIP  10.96.0.10    80/TCP\n  redis   ClusterIP  10.96.0.20    6379/TCP\n  api     NodePort   10.96.0.30    8080:31234/TCP\n");}
    else if(strcmp(args[1],"ns")==0){vga_puts("  default\n  kube-system\n  kube-public\n  monitoring\n");}
    else if(strcmp(args[1],"logs")==0){if(argc<3){vga_puts("Usage: k9s logs <pod>\n");return;}vga_puts("[");vga_puts(args[2]);vga_puts("]\n  12:00:00 INFO Server started\n");}
    else if(strcmp(args[1],"tree")==0){vga_puts("  deployment/web\n  +-- replicaset/web-7d8f\n  |   +-- pod/web-x9k2l\n  |   +-- container/nginx\n");} else { vga_puts("k9s: unknown command\n"); }
}
static void cmd_lens52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: lens <clusters|connect|status|metrics>\n");return;}
    if(strcmp(args[1],"clusters")==0){vga_puts("Lens - Kubernetes IDE\n  [x] kind-cluster (Ready)\n  [ ] minikube (Stopped)\n  [x] production (Ready)\n");}
    else if(strcmp(args[1],"connect")==0){vga_puts("Connecting to cluster...\n  Dashboard: http://localhost:32768\n");}
    else if(strcmp(args[1],"status")==0){vga_puts("Cluster: kind-cluster\n  K8s: 1.28.3  Nodes: 1\n  Pods: 8  Services: 5  Deployments: 3\n");}
    else if(strcmp(args[1],"metrics")==0){vga_puts("CPU: 450m/2000m (22.5%)\nMemory: 1.2Gi/4Gi (30.0%)\nStorage: 5.2Gi/50Gi (10.4%)\nPods: 8/110\n");} else { vga_puts("lens: unknown command\n"); }
}
static void cmd_rancher52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: rancher <clusters|apps|projects|users|status>\n");return;}
    if(strcmp(args[1],"clusters")==0){vga_puts("  Name        Provider  State   Version\n  local       Local     Active  v1.28.3\n  staging     EKS       Active  v1.27.8\n  production  EKS       Active  v1.27.8\n");}
    else if(strcmp(args[1],"apps")==0){vga_puts("  prometheus     monitoring   v2.48.0  Deployed\n  grafana        monitoring   v7.0.0   Deployed\n  cert-manager   security     v1.13.3  Deployed\n");}
    else if(strcmp(args[1],"projects")==0){vga_puts("  Default     System   3 namespaces\n  Platform     Default  5 namespaces\n");}
    else if(strcmp(args[1],"users")==0){vga_puts("  admin    Global Admin\n  dev      Project User\n  viewer   Read Only\n");}
    else if(strcmp(args[1],"status")==0){vga_puts("Rancher v2.8.0\n  Clusters: 4  Users: 12  Apps: 8\n");} else { vga_puts("rancher: unknown command\n"); }
}
static void cmd_argocd52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: argocd <apps|status|sync|login|repo>\n");return;}
    if(strcmp(args[1],"apps")==0){vga_puts("  Name          Status   Health   Sync\n  web-app       Synced   Healthy  UpToDate\n  monitoring    Synced   Healthy  UpToDate\n  api-service   Degraded Degraded OutOfSync\n");}
    else if(strcmp(args[1],"status")==0){vga_puts("ArgoCD v2.9.3\n  Server: Running\n  Repo: Connected\n  Apps: 4 (3 Synced, 1 Degraded)\n");}
    else if(strcmp(args[1],"sync")==0){if(argc<3){vga_puts("Usage: argocd sync <app>\n");return;}vga_puts("Syncing ");vga_puts(args[2]);vga_puts("...\n  Deployment: Synced\n  Service: Synced\n  Ingress: Synced\n  Done\n");}
    else if(strcmp(args[1],"login")==0){vga_puts("Logged in to argocd-server\n");}
    else if(strcmp(args[1],"repo")==0){vga_puts("  URL                           Type\n  https://github.com/org/apps  git\n  https://charts.example.com   helm\n");} else { vga_puts("argocd: unknown command\n"); }
}
static void cmd_flux52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: flux <get|suspend|resume|reconcile|logs>\n");return;}
    if(strcmp(args[1],"get")==0){vga_puts("  Name          Status  Last Transition\n  web-app       Ready   2m\n  monitoring    Ready   5m\n  crds          Ready   10m\n");}
    else if(strcmp(args[1],"suspend")==0){if(argc<3){vga_puts("Usage: flux suspend <resource>\n");return;}vga_puts("Suspended ");vga_puts(args[2]);vga_putchar('\n');}
    else if(strcmp(args[1],"resume")==0){if(argc<3){vga_puts("Usage: flux resume <resource>\n");return;}vga_puts("Resumed ");vga_puts(args[2]);vga_putchar('\n');}
    else if(strcmp(args[1],"reconcile")==0){vga_puts("Reconciling sources...\n  GitRepository/apps: finished\n  HelmRepository/charts: finished\n");}
    else if(strcmp(args[1],"logs")==0){vga_puts("12:00:00 INFO Reconciliation finished\n12:05:00 INFO Starting reconciliation\n");} else { vga_puts("flux: unknown command\n"); }
}
static void cmd_tekton52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: tekton <pipelines|tasks|runs|logs|triggers>\n");return;}
    if(strcmp(args[1],"pipelines")==0){vga_puts("  Name          Tasks  Status    Age\n  build-push     3     Succeeded  2d\n  deploy-staging 4     Succeeded  1d\n  e2e-tests      2     Running    5m\n");}
    else if(strcmp(args[1],"tasks")==0){vga_puts("  Name         Steps  Age\n  git-clone     1      7d\n  buildah       1      7d\n  deploy        1      5d\n  pytest        1      3d\n");}
    else if(strcmp(args[1],"runs")==0){vga_puts("  Name                Pipeline     Status    Duration\n  build-push-run-abc  build-push   Succeeded  45s\n  deploy-run-def      deploy       Succeeded  2m\n");}
    else if(strcmp(args[1],"logs")==0){vga_puts("[git-clone] Cloning repo\n[buildah] Building image\n  Step 1/5: FROM gcr.io/distroless/static\n");}
    else if(strcmp(args[1],"triggers")==0){vga_puts("  github-listener  Port: 8080\n  Bindings: github-push\n  Templates: build-template\n");} else { vga_puts("tekton: unknown command\n"); }
}
static void cmd_concourse52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: concourse <pipelines|jobs|builds|resources|fly>\n");return;}
    if(strcmp(args[1],"pipelines")==0){vga_puts("  Name          Paused  Groups\n  main          no      [app, infra]\n  deployments   no      [staging, prod]\n");}
    else if(strcmp(args[1],"jobs")==0){vga_puts("  Name           Finished  Status\n  build-app      #42       Succeeded 2d\n  test-integ     #38       Succeeded 1d\n  deploy-staging #35       Succeeded 5h\n");}
    else if(strcmp(args[1],"builds")==0){vga_puts("  ID   Pipeline  Job          Status\n  #42  main      build-app    succeeded\n  #41  main      test-integ   failed\n");}
    else if(strcmp(args[1],"resources")==0){vga_puts("  Name          Type   Checked\n  git-source    git    5m ago\n  docker-image  docker 10m ago\n");}
    else if(strcmp(args[1],"fly")==0){vga_puts("Fly v7.9.2\n  Target: concourse\n  Team: main\n  User: admin\n");} else { vga_puts("concourse: unknown command\n"); }
}
static void cmd_jenkins52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: jenkins <status|jobs|build|logs|plugins>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("Jenkins 2.440.1 LTS\n  URL: http://localhost:8080\n  Nodes: 3 (1 master, 2 agents)\n  Jobs: 24  Executing: 1\n  Plugins: 87\n");}
    else if(strcmp(args[1],"jobs")==0){vga_puts("  Name               Status  Last Build\n  web-pipeline       Success #142 (2d)\n  api-service        Success #89  (1d)\n  integration-tests  Failure #56  (6h)\n  deploy-prod        Success #23  (12h)\n");}
    else if(strcmp(args[1],"build")==0){if(argc<3){vga_puts("Usage: jenkins build <job>\n");return;}vga_puts("Started build ");vga_puts(args[2]);vga_putchar('\n');vga_puts("  Status: In Progress\n  Agent: agent-1\n");}
    else if(strcmp(args[1],"logs")==0){vga_puts("12:00:00 Started by admin\n12:00:01 Checkout: SCM\n12:00:02 [stage] Building...\n12:00:10 [stage] Testing...\n12:00:25 [stage] Success!\n");}
    else if(strcmp(args[1],"plugins")==0){vga_puts("  Name        Version  Status\n  Pipeline    2.7      Active\n  Git         5.2.0    Active\n  Docker      1.4      Active\n  BlueOcean   1.27.9   Active\n");} else { vga_puts("jenkins: unknown command\n"); }
}
static void cmd_gitlab_ci52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: gitlab-ci <pipelines|jobs|variables|runners|pages>\n");return;}
    if(strcmp(args[1],"pipelines")==0){vga_puts("  ID   Status    Ref    Trigger\n  142  success   main   push\n  141  failed    feat   merge_request\n  140  success   main   push\n");}
    else if(strcmp(args[1],"jobs")==0){vga_puts("  Name          Stage    Status\n  build         build    success\n  test-unit     test     success\n  test-integ    test     success\n  deploy-prod   deploy   manual\n");}
    else if(strcmp(args[1],"variables")==0){vga_puts("  Name             Protected  Env\n  DOCKER_PASSWORD  yes        prod\n  SSH_KEY          yes        prod\n  CI_JOB_TOKEN     no\n");}
    else if(strcmp(args[1],"runners")==0){vga_puts("  Name      Status  Platform\n  runner-01 online  docker\n  runner-02 online  docker\n  runner-03 offline kubernetes\n");}
    else if(strcmp(args[1],"pages")==0){vga_puts("  URL: https://byo-os.gitlab.io\n  Status: Published\n");} else { vga_puts("gitlab-ci: unknown command\n"); }
}
static void cmd_circle_ci52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: circleci <pipelines|projects|build|insights|env>\n");return;}
    if(strcmp(args[1],"pipelines")==0){vga_puts("  ID     Status    Branch  Created\n  247    success   main    2h ago\n  246    failed    feat    1d ago\n  245    success   main    2d ago\n");}
    else if(strcmp(args[1],"projects")==0){vga_puts("  org/web-app       Total:247  Success:94%\n  org/api-service   Total:156  Success:97%\n  org/mobile-app    Total:89   Success:91%\n");}
    else if(strcmp(args[1],"build")==0){vga_puts("Build #247\n  Branch: main\n  Commit: a1b2c3d\n  Status: SUCCESS\n  Workflows: build-test(2m15s), deploy(1m30s)\n");}
    else if(strcmp(args[1],"insights")==0){vga_puts("Last 30 days:\n  Total: 247  Passed: 232 (94%)  Failed: 15\n  Avg: 3m45s  Slowest: 12m20s\n");}
    else if(strcmp(args[1],"env")==0){vga_puts("  DOCKER_PASSWORD  (masked)\n  AWS_ACCESS_KEY   (masked)\n");} else { vga_puts("circleci: unknown command\n"); }
}
static void cmd_travis_ci52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: travis <status|builds|requests|encrypt|lint>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("Build: #234  Status: Passed\n  Branch: main\n  Commit: a1b2c3d\n  Duration: 4m 32s  Jobs: 4/4\n");}
    else if(strcmp(args[1],"builds")==0){vga_puts("  #234  Passed  main  4m32s  a1b2c3d\n  #233  Failed  dev   2m10s  b2c3d4e\n  #232  Passed  main  3m55s  c3d4e5f\n");}
    else if(strcmp(args[1],"requests")==0){vga_puts("  Build #235  Branch: feat  Status: queued\n");}
    else if(strcmp(args[1],"encrypt")==0){vga_puts("  AWS_KEY: secure!abc123...\n  DOCKER_PASS: secure!789...\n");}
    else if(strcmp(args[1],"lint")==0){vga_puts("Validating .travis.yml\n  No warnings or errors\n");} else { vga_puts("travis: unknown command\n"); }
}
static void cmd_actions52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: gh-actions <workflows|runs|secrets|act|lint>\n");return;}
    if(strcmp(args[1],"workflows")==0){vga_puts("  Name          Status  Trigger\n  CI            Active  push, pull_request\n  Deploy        Active  push (main)\n  Release       Active  tag\n");}
    else if(strcmp(args[1],"runs")==0){vga_puts("  #42 CI      success  2m15s  main    a1b2c3d\n  #41 Deploy  success  5m30s  main    a1b2c3d\n  #40 CI      failure  1m02s  feature b2c3d4e\n");}
    else if(strcmp(args[1],"secrets")==0){vga_puts("  DOCKER_PASSWORD  3d ago\n  AWS_ACCESS_KEY   1w ago\n  DEPLOY_KEY       2w ago\n");}
    else if(strcmp(args[1],"act")==0){vga_puts("Running with act...\n  [build] Node.js Setup\n  [build] Install Dependencies\n  [build] Lint & Test\n  [build] Build\n  Success  Duration: 2m15s\n");}
    else if(strcmp(args[1],"lint")==0){vga_puts("  .github/workflows/ci.yml      OK\n  .github/workflows/deploy.yml   OK\n  .github/workflows/release.yml  OK\n");} else { vga_puts("gh-actions: unknown command\n"); }
}
static void cmd_terraform52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: terraform <init|plan|apply|destroy|state|fmt>\n");return;}
    if(strcmp(args[1],"init")==0){vga_puts("Initializing...\n  aws v5.34.0 downloaded\n  kubernetes v2.25.0 downloaded\n  Successfully initialized!\n");}
    else if(strcmp(args[1],"plan")==0){vga_puts("Plan: 8 to add, 2 to change, 1 to destroy.\n  + aws_instance.web      (new)\n  + aws_security_group.sg (new)\n  + aws_lb.main           (new)\n  ~ aws_instance.api      (update)\n  - aws_instance.old      (destroy)\n  Cost: ~$125.40/month\n");}
    else if(strcmp(args[1],"apply")==0){vga_puts("Applying...\n  sg: Created after 3s\n  web: Created after 15s\n  api: Updated after 5s\n  old: Destroyed after 10s\n  Complete! 8+, 2~, 1-\n");}
    else if(strcmp(args[1],"destroy")==0){vga_puts("Destroying...\n  web: Destroyed after 10s\n  sg: Destroyed after 2s\n  Complete! 8 destroyed\n");}
    else if(strcmp(args[1],"state")==0){vga_puts("Resources:\n  aws_instance.web        i-0abc123\n  aws_instance.api        i-0def456\n  aws_security_group.sg  sg-0abc123\n");}
    else if(strcmp(args[1],"fmt")==0){vga_puts("  main.tf    (rewritten)\n  vars.tf    (rewritten)\n  outputs.tf (unchanged)\n");} else { vga_puts("terraform: unknown command\n"); }
}
static void cmd_packer52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: packer <init|build|validate|inspect|fmt>\n");return;}
    if(strcmp(args[1],"init")==0){vga_puts("Installing plugins...\n  hcl2 v1.0.10\n  amazon-ebs v1.3.0\n  Installed in 2s\n");}
    else if(strcmp(args[1],"build")==0){vga_puts("Building...\n  Preparing AMI Filters...\n  Launching instance...\n  Waiting for AMI ready...\n  AMI: ami-0abc123\n  Built in 180s\n");}
    else if(strcmp(args[1],"validate")==0){vga_puts("Configuration valid.\n");}
    else if(strcmp(args[1],"inspect")==0){vga_puts("  Builder: amazon-ebs\n  Source AMI: ami-0abc123\n  Instance: t3.micro\n");}
    else if(strcmp(args[1],"fmt")==0){vga_puts("  template.pkr.hcl (rewritten)\n");} else { vga_puts("packer: unknown command\n"); }
}
static void cmd_vagrant52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: vagrant <up|halt|destroy|status|ssh|box|provision>\n");return;}
    if(strcmp(args[1],"up")==0){vga_puts("Bringing machine up with hyperv...\n  Importing ubuntu/jammy64\n  Configuring VM\n  Forwarding: 22->2222, 80->8080\n  Booting VM\n  Machine ready!\n");}
    else if(strcmp(args[1],"halt")==0){vga_puts("Shutdown VM...\n  Guest power finished\n");}
    else if(strcmp(args[1],"destroy")==0){vga_puts("Force shutdown...\n  VM destroyed\n");}
    else if(strcmp(args[1],"status")==0){vga_puts("default    running (hyperv)\n");}
    else if(strcmp(args[1],"ssh")==0){vga_puts("SSH connecting to 127.0.0.1:2222...\n  Welcome to Ubuntu 22.04\n");}
    else if(strcmp(args[1],"box")==0){vga_puts("  Name          Provider  Version\n  ubuntu/jammy  hyperv    3.1.0\n  debian/bookw  hyperv    12.0.0\n");}
    else if(strcmp(args[1],"provision")==0){vga_puts("Running provisioner...\n  Installing packages...\n  Provisioning complete!\n");} else { vga_puts("vagrant: unknown command\n"); }
}
static void cmd_ansible52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: ansible <playbook|inventory|ping|ad-hoc|vault>\n");return;}
    if(strcmp(args[1],"playbook")==0){vga_puts("PLAY [web_servers]\n\n  TASK [Gathering Facts]\n    ok: web01\n    ok: web02\n\n  TASK [Install nginx]\n    changed: web01\n    changed: web02\n\n  PLAY RECAP: web01 ok=3 c=1, web02 ok=3 c=1\n");}
    else if(strcmp(args[1],"inventory")==0){vga_puts("  web_servers:\n    web01: 10.0.1.10\n    web02: 10.0.1.11\n  db_servers:\n    db01:  10.0.2.10\n");}
    else if(strcmp(args[1],"ping")==0){vga_puts("web01 | SUCCESS => {ping: pong}\nweb02 | SUCCESS => {ping: pong}\n");}
    else if(strcmp(args[1],"ad-hoc")==0){vga_puts("ansible web_servers -m shell -a uptime\n  web01 | CHANGED: 12:00:00 up 14d\n  web02 | CHANGED: 12:00:00 up 10d\n");}
    else if(strcmp(args[1],"vault")==0){vga_puts("Encrypted files:\n  group_vars/all/vault.yml\n  vars/secrets.yml\n");} else { vga_puts("ansible: unknown command\n"); }
}
static void cmd_puppet52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: puppet <apply|agent|server|catalog|facts>\n");return;}
    if(strcmp(args[1],"apply")==0){vga_puts("Compiled catalog for byo-os\n  Notice: Package[nginx]: created\n  Notice: File[/etc/nginx/nginx.conf]: defined\n  Notice: Service[nginx]: ensure: running\n  Applied in 2.34s\n");}
    else if(strcmp(args[1],"agent")==0){vga_puts("Running: Yes\n  Last run: 5m ago\n  Run time: 12.45s\n  Changes: 3\n  Server: https://puppet.example.com\n");}
    else if(strcmp(args[1],"server")==0){vga_puts("Puppet Server 8.5.0\n  Status: Running\n  Nodes: 24 (22 active)\n  Catalog compile: 1.2s avg\n");}
    else if(strcmp(args[1],"catalog")==0){vga_puts("Total resources: 45\n  Corrective changes: 2\n  Run time: 2.34s\n");}
    else if(strcmp(args[1],"facts")==0){vga_puts("  OS: Ubuntu 22.04\n  Kernel: 5.15.0\n  CPUs: 4  RAM: 16GB\n");} else { vga_puts("puppet: unknown command\n"); }
}
static void cmd_chef52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: chef <status|node|cookbook|knife|policy>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("Chef Infra Server 15.8.2\n  Nodes: 32  Cookbooks: 45\n  Environments: 4  Roles: 8\n  Status: Healthy\n");}
    else if(strcmp(args[1],"node")==0){vga_puts("  Name            OS        Status  Last Check-in\n  web01.byo       Ubuntu    ok      5m ago\n  web02.byo       Ubuntu    ok      8m ago\n  db01.byo        Debian    ok      2m ago\n");}
    else if(strcmp(args[1],"cookbook")==0){vga_puts("  Name      Version  Deps\n  nginx     12.1.0   apt\n  docker    7.4.1    none\n  postgres  11.1.0   apt\n");}
    else if(strcmp(args[1],"knife")==0){vga_puts("  node list: web01, web02, db01\n  cookbook list: nginx(12.1), docker(7.4)\n");}
    else if(strcmp(args[1],"policy")==0){vga_puts("  production  rev: abc123  cookbooks: 12\n  staging     rev: ghi456  cookbooks: 10\n");} else { vga_puts("chef: unknown command\n"); }
}
static void cmd_salt52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: salt <status|state|apply|pillar|key>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("Salt Master 3007.0\n  Status: Running\n  Minions: 8 (8 connected)\n");}
    else if(strcmp(args[1],"state")==0){vga_puts("Executing highstate...\n  web01:\n    ID: nginx  Result: True\n    Comment: already installed\n  Succeeded: 5  Failed: 0\n");}
    else if(strcmp(args[1],"apply")==0){vga_puts("Applying state...\n  Succeeded: 5  Failed: 0\n");}
    else if(strcmp(args[1],"pillar")==0){vga_puts("  web01:\n    nginx:\n      port: 80\n      ssl_port: 443\n    users: [admin, deploy]\n");}
    else if(strcmp(args[1],"key")==0){vga_puts("  Accepted: web01, web02, db01, app01\n  Rejected: 0  Pending: 1\n");} else { vga_puts("salt: unknown command\n"); }
}
static void cmd_puppeteer52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: puppeteer <launch|screenshot|pdf|evaluate|emulate>\n");return;}
    if(strcmp(args[1],"launch")==0){vga_puts("Launching Chromium 121.0...\n  Headless: true\n  Viewport: 1920x1080\n  Connected\n");}
    else if(strcmp(args[1],"screenshot")==0){vga_puts("Taking screenshot...\n  Target: http://localhost:3000\n  Output: screenshot.png (1920x1080, 245KB)\n");}
    else if(strcmp(args[1],"pdf")==0){vga_puts("Generating PDF...\n  Output: page.pdf (A4, 3 pages, 1.2MB)\n");}
    else if(strcmp(args[1],"evaluate")==0){vga_puts("Evaluating JS...\n  document.title = BYO-OS Dashboard\n  FCP: 320ms\n");}
    else if(strcmp(args[1],"emulate")==0){vga_puts("  iPhone 14 Pro: 393x852 DPR:3\n  iPad: 820x1180 DPR:2\n  Desktop: 1920x1080\n");} else { vga_puts("puppeteer: unknown command\n"); }
}
static void cmd_playwright52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: playwright <test|codegen|install|trace|show-trace>\n");return;}
    if(strcmp(args[1],"test")==0){vga_puts("Running 24 tests, 4 workers...\n  login.spec.ts        (8.2s)\n  navigation.spec.ts   (3.1s)\n  dashboard.spec.ts    (5.7s)\n  api.spec.ts          FAILED (12.1s)\n  23 passed, 1 failed (28.4s)\n");}
    else if(strcmp(args[1],"codegen")==0){vga_puts("Recording...\n  Browser: Chromium\n  Output: tests/recorded.spec.ts\n  Generated 45 lines\n");}
    else if(strcmp(args[1],"install")==0){vga_puts("Installing browsers...\n  chromium v121.0  185MB\n  firefox  v121.0  210MB\n  webkit   v17.4   165MB\n  All installed!\n");}
    else if(strcmp(args[1],"trace")==0){vga_puts("Trace: trace.zip\n  Duration: 12.4s  Steps: 24\n  Screenshots: 8  Size: 2.3MB\n");}
    else if(strcmp(args[1],"show-trace")==0){vga_puts("Opening trace viewer...\n  http://localhost:9323/trace\n  24 steps, 8 screenshots\n");} else { vga_puts("playwright: unknown command\n"); }
}
static void cmd_selenium52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: selenium <status|test|grid|hub|console>\n");return;}
    if(strcmp(args[1],"status")==0){vga_puts("Selenium Grid 4.16.1\n  Nodes: 4  Sessions: 8/16\n  Hub: http://localhost:4444\n  Browsers: chrome(3), firefox(1)\n");}
    else if(strcmp(args[1],"test")==0){vga_puts("Running test suite...\n  TestLogin:         PASSED (2.3s)\n  TestDashboard:     PASSED (1.8s)\n  TestNavigation:    FAILED (0.9s)\n  TestFormSubmit:    PASSED (3.1s)\n  3 passed, 1 failed\n");}
    else if(strcmp(args[1],"grid")==0){vga_puts("  Hub: http://localhost:4444\n  Node1: chrome 121  (2/4 sessions)\n  Node2: chrome 121  (1/4 sessions)\n  Node3: firefox 121 (1/4 sessions)\n  Node4: chrome 121  (0/4 sessions)\n");}
    else if(strcmp(args[1],"hub")==0){vga_puts("Hub: standalone\n  Port: 4444  Timeout: 300s\n  Max sessions: 4/node\n");}
    else if(strcmp(args[1],"console")==0){vga_puts("Console: http://localhost:4444/ui\n  Sessions: 2  Queued: 0\n");} else { vga_puts("selenium: unknown command\n"); }
}
static void cmd_cypress52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: cypress <run|open|verify|info|cache>\n");return;}
    if(strcmp(args[1],"run")==0){vga_puts("Running Cypress tests...\n  Tests: 12  Passes: 11  Fail: 1\n  Duration: 42s  Specs: 4\n");}
    else if(strcmp(args[1],"open")==0){vga_puts("Opening Test Runner...\n  URL: http://localhost:8080\n  Browser: Electron 118\n  Specs: 12\n");}
    else if(strcmp(args[1],"verify")==0){vga_puts("Cypress 13.6.1\n  Chrome 121  Node 18.19.0\n  Verified!\n");}
    else if(strcmp(args[1],"info")==0){vga_puts("  Cypress: 13.6.1\n  Browser: Chrome 121\n  Node: 18.19.0\n  OS: linux x64\n");}
    else if(strcmp(args[1],"cache")==0){vga_puts("  ~/.cache/Cypress\n  Version: 13.6.1 (189MB)\n");} else { vga_puts("cypress: unknown command\n"); }
}
static void cmd_jmeter52(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: jmeter <run|gui|report|server|nongui>\n");return;}
    if(strcmp(args[1],"run")==0){vga_puts("Running test plan...\n  Threads: 50  Ramp-up: 10s  Duration: 60s\n  Total: 15234  Errors: 23 (0.15%)\n  Avg: 45ms  95th: 120ms\n  Throughput: 253.9/s\n");}
    else if(strcmp(args[1],"gui")==0){vga_puts("Launching GUI...\n  Apache JMeter 5.6.3\n  Java: OpenJDK 17.0.9\n  Loaded: api-test.jmx\n");}
    else if(strcmp(args[1],"report")==0){vga_puts("Generating report...\n  Input: results.jtl\n  Charts:\n    Response Times Over Time    OK\n    Throughput Over Time        OK\n  Output: http://localhost/report/\n");}
    else if(strcmp(args[1],"server")==0){vga_puts("Server Status:\n  Port: 1099\n  Mode: distributed\n  Nodes: 3 (3 connected)\n");}
    else if(strcmp(args[1],"nongui")==0){vga_puts("Non-GUI mode:\n  Plan: api-test.jmx\n  Results: results.jtl\n  PID: 12345 (background)\n");} else { vga_puts("jmeter: unknown command\n"); }
}
