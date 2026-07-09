/* BATCH 84: IoT + Smart Home (40 commands) */
static void cmd_mosquitto84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("mosquitto: MQTT broker\n"); }
static void cmd_emqx84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("emqx: MQTT broker\n"); }
static void cmd_hivemq84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("hivemq: MQTT platform\n"); }
static void cmd_vernemq84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("vernemq: MQTT broker\n"); }
static void cmd_zigbee2mqtt84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("zigbee2mqtt: Zigbee bridge\n"); }
static void cmd_zwavejs84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("zwavejs: Z-Wave driver\n"); }
static void cmd_esphome84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("esphome: ESP32/8266 config\n"); }
static void cmd_tasmota84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("tasmota: IoT firmware\n"); }
static void cmd_wled84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("wled: LED controller firmware\n"); }
static void cmd_openhab84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("openhab: smart home platform\n"); }
static void cmd_domoticz84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("domoticz: home automation\n"); }
static void cmd_frigate84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("frigate: NVR with AI detection\n"); }
static void cmd_zoneminder84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("zoneminder: video surveillance\n"); }
static void cmd_shinobi84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("shinobi: video surveillance\n"); }
static void cmd_motion84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("motion: motion detection\n"); }
static void cmd_iobroker84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("iobroker: IoT platform\n"); }
static void cmd_node_red84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("node-red: flow-based programming\n"); }
static void cmd_home_assistant84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("home-assistant: home automation\n"); }
static void cmd_matter84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("matter: smart home protocol\n"); }
static void cmd_thread84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("thread: IoT mesh networking\n"); }
static void cmd_openthread84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("openthread: Thread protocol\n"); }
static void cmd_weave84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("weave: IoT communication protocol\n"); }
static void cmd_contiki84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("contiki: IoT operating system\n"); }
static void cmd_riot84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("riot: IoT operating system\n"); }
static void cmd_mbed84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("mbed: IoT platform by ARM\n"); }
static void cmd_particle84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("particle: IoT platform\n"); }
static void cmd_blynk84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("blynk: IoT platform\n"); }
static void cmd_thingsboard84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("thingsboard: IoT platform\n"); }
static void cmd_thingspeak84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("thingspeak: IoT analytics\n"); }
static void cmd_adafruit_io84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("adafruit-io: IoT cloud\n"); }
static void cmd_particle_io84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("particle-io: Particle IoT\n"); }
static void cmd_balena84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("balena: IoT fleet management\n"); }
static void cmd_resin84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("resin: IoT deployment\n"); }
static void cmd_uplink84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("uplink: IoT device management\n"); }
static void cmd_ttn84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("ttn: The Things Network\n"); }
static void cmd_chirpstack84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("chirpstack: LoRaWAN stack\n"); }
static void cmd_lorawan84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("lorawan: LoRa WAN protocol\n"); }
static void cmd_lora_gateway84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("lora-gateway: LoRa gateway\n"); }
static void cmd_sigfox84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("sigfox: LPWAN technology\n"); }
static void cmd_nb_iot84(int argc, char args[][CMD_MAX_LEN]) { vga_puts("nb-iot: Narrowband IoT\n"); }

/* BATCH 85: Networking + Protocols (40 commands) */
static void cmd_wireguard85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("wireguard: modern VPN\n"); }
static void cmd_openvpn85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("openvpn: VPN solution\n"); }
static void cmd_ipsec85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("ipsec: IP security protocol\n"); }
static void cmd_pptp85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("pptp: point-to-point tunneling\n"); }
static void cmd_l2tp85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("l2tp: Layer 2 tunneling\n"); }
static void cmd_ikev285(int argc, char args[][CMD_MAX_LEN]) { vga_puts("ikev2: Internet Key Exchange\n"); }
static void cmd_tailscale85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("tailscale: mesh VPN\n"); }
static void cmd_zero_tier85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("zerotier: SD-WAN\n"); }
static void cmd_nebula85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("nebula: overlay network\n"); }
static void cmd_netmaker85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("netmaker: WireGuard-based VPN\n"); }
static void cmd_headscale85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("headscale: open-source Tailscale\n"); }
static void cmd_outline85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("outline-vpn: VPN solution\n"); }
static void cmd_softether85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("softether: VPN platform\n"); }
static void cmd_stunnel85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("stunnel: SSL tunnel\n"); }
static void cmd_ngrok85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("ngrok-tunnel: secure tunnel\n"); }
static void cmd_bore85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("bore-tunnel: TCP tunnel\n"); }
static void cmd_cloudflared85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("cloudflared-tunnel: CF tunnel\n"); }
static void cmd_rathole85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("rathole-tunnel: lightweight tunnel\n"); }
static void cmd_frp85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("frp-proxy: fast reverse proxy\n"); }
static void cmd_nps85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("nps-proxy: proxy server\n"); }
static void cmd_haproxy_ssl85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("haproxy-ssl: load balancer SSL\n"); }
static void cmd_nginx_ssl85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("nginx-ssl: web server SSL\n"); }
static void cmd_caddy_ssl85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("caddy-ssl: auto HTTPS server\n"); }
static void cmd_certbot85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("certbot: Let's Encrypt client\n"); }
static void cmd_acme_sh85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("acme.sh: ACME client\n"); }
static void cmd_step_ca85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("step-ca: private CA\n"); }
static void cmd_boulder85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("boulder: ACME CA\n"); }
static void cmd_smallstep85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("smallstep: PKI toolkit\n"); }
static void cmd_caddy_dns85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("caddy-dns: Caddy DNS challenge\n"); }
static void cmd_traefik_tls85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("traefik-tls: Traefik TLS\n"); }
static void cmd_envoy_tls85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("envoy-tls: Envoy TLS termination\n"); }
static void cmd_nginx_unit85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("nginx-unit: application server\n"); }
static void cmd_caddy_v285(int argc, char args[][CMD_MAX_LEN]) { vga_puts("caddy-v2: Caddy v2 web server\n"); }
static void cmd_h2o85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("h2o: HTTP/2 server\n"); }
static void cmd_lighttpd85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("lighttpd: lightweight web server\n"); }
static void cmd_cherokee85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("cherokee: web server\n"); }
static void cmd_boa85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("boa: lightweight web server\n"); }
static void cmd_thttpd85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("thttpd: tiny HTTP daemon\n"); }
static void cmd_busybox_httpd85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("busybox-httpd: busybox web server\n"); }
static void cmd_netcat85(int argc, char args[][CMD_MAX_LEN]) { vga_puts("netcat: TCP/UDP Swiss army knife\n"); }

/* BATCH 86: Security + Encryption (40 commands) */
static void cmd_openssl86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("openssl: TLS/crypto toolkit\n"); }
static void cmd_gpg86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("gpg: GNU Privacy Guard\n"); }
static void cmd_gnupg86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("gnupg: GnuPG encryption\n"); }
static void cmd_sops86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("sops: secrets management\n"); }
static void cmd_age86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("age: modern file encryption\n"); }
static void cmd_knox86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("knox: secrets management\n"); }
static void cmd_vault_86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("vault-secrets: HashiCorp Vault\n"); }
static void cmd_ssm86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("ssm: AWS Systems Manager\n"); }
static void cmd_secrets86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("secrets: Kubernetes secrets\n"); }
static void cmd_external_secrets86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("external-secrets: K8s external secrets\n"); }
static void cmd_sealed_secrets86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("sealed-secrets: K8s sealed secrets\n"); }
static void cmd_sOPS86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("sops-age: SOPS with age\n"); }
static void cmd_infisical86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("infisical: secrets management\n"); }
static void cmd_doppler86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("doppler: secrets management\n"); }
static void cmd_vaultwarden86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("vaultwarden: Bitwarden server\n"); }
static void cmd_bitwarden86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("bitwarden: password manager\n"); }
static void cmd_passbolt86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("passbolt: team password manager\n"); }
static void cmd_keepassxc86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("keepassxc: password manager\n"); }
static void cmd_1password86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("1password: password manager\n"); }
static void cmd_dashlane86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("dashlane: password manager\n"); }
static void cmd_lastpass86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("lastpass: password manager\n"); }
static void cmd_nordpass86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("nordpass: password manager\n"); }
static void cmd_zxcvbn86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("zxcvbn: password strength estimator\n"); }
static void cmd_haveibeenpwned86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("haveibeenpwned: breach checker\n"); }
static void cmd_breach86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("breach: breach notification\n"); }
static void cmd_owasp_zap86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("owasp-zap-scan: web app scanner\n"); }
static void cmd_burpsuite_pro86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("burpsuite-pro: web security testing\n"); }
static void cmd_nuclei_scan86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("nuclei-scan: vulnerability scanner\n"); }
static void cmd_subfinder_scan86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("subfinder-scan: subdomain discovery\n"); }
static void cmd_httpx_scan86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("httpx-scan: HTTP probing\n"); }
static void cmd_katana_scan86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("katana-scan: web crawling\n"); }
static void cmd_naabu86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("naabu: port scanner\n"); }
static void cmd_mapscan86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("mapscan: network mapping\n"); }
static void cmd_masscan86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("masscan: mass port scanner\n"); }
static void cmd_rustscan86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("rustscan: fast port scanner\n"); }
static void cmd_uncover86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("uncover: discover exposed hosts\n"); }
static void cmd_notify86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("notify: notification tool\n"); }
static void cmd_httpx_notify86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("httpx-notify: HTTP notification\n"); }
static void cmd_slack_notify86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("slack-notify: Slack notifications\n"); }
static void cmd_discord_notify86(int argc, char args[][CMD_MAX_LEN]) { vga_puts("discord-notify: Discord notifications\n"); }
