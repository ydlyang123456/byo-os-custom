# inject_291_294.py - More specialized tools
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 291: Networking & Proxy =====
b291_decls = """static void cmd_traefik291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_envoy291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_consul291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vault291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nomad291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_waypoint291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_boundary291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_packer291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_terraform291_cloud(int argc, char args[][CMD_MAX_LEN]);
static void cmd_argocd291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_flux291(int argc, char args[][CMD_MAX_LEN]);
static void cmd_argo291_rollouts(int argc, char args[][CMD_MAX_LEN]);
"""

b291_entries = """    /* Batch 291: Networking & Proxy */
    {"traefik", cmd_traefik291}, {"envoy", cmd_envoy291}, {"consul", cmd_consul291},
    {"vault", cmd_vault291}, {"nomad", cmd_nomad291}, {"waypoint", cmd_waypoint291},
    {"boundary", cmd_boundary291}, {"packer", cmd_packer291}, {"terraform-cloud", cmd_terraform291_cloud},
    {"argocd", cmd_argocd291}, {"flux", cmd_flux291}, {"argo-rollouts", cmd_argo291_rollouts},
"""

b291_funcs = """/* ===== Batch 291: Networking & Proxy ===== */
static void cmd_traefik291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Traefik: cloud-native reverse proxy\\n");
    vga_puts("traefik: listening on :80 and :443\\n");
}
static void cmd_envoy291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Envoy: service proxy\\n");
    vga_puts("envoy: 3 clusters, 5 routes\\n");
}
static void cmd_consul291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Consul: service discovery\\n");
    vga_puts("consul: 5 services registered\\n");
}
static void cmd_vault291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("HashiCorp Vault: secrets management\\n");
    vga_puts("vault: sealed: false\\n");
}
static void cmd_nomad291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Nomad: workload orchestrator\\n");
    vga_puts("nomad: 3 jobs, 5 allocations\\n");
}
static void cmd_waypoint291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Waypoint: app deployment platform\\n");
}
static void cmd_boundary291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Boundary: secure remote access\\n");
}
static void cmd_packer291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Packer: image builder\\n");
    vga_puts("packer: build complete\\n");
}
static void cmd_terraform291_cloud(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Terraform Cloud: infrastructure as code\\n");
}
static void cmd_argocd291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ArgoCD: GitOps continuous delivery\\n");
    vga_puts("argocd: 5 applications synced\\n");
}
static void cmd_flux291(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Flux: GitOps toolkit\\n");
    vga_puts("flux: reconciliation complete\\n");
}
static void cmd_argo291_rollouts(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Argo Rollouts: progressive delivery\\n");
}
"""

# ===== BATCH 292: More DevOps =====
b292_decls = """static void cmd_argo292_workflows(int argc, char args[][CMD_MAX_LEN]);
static void cmd_event292_routing(int argc, char args[][CMD_MAX_LEN]);
static void cmd_knative292(int argc, char args[][CMD_MAX_LEN]);
static void cmd_openfaas292(int argc, char args[][CMD_MAX_LEN]);
static void cmd_fission292(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kubeless292(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_camel292(int argc, char args[][CMD_MAX_LEN]);
static void cmd_camel292_k(int argc, char args[][CMD_MAX_LEN]);
static void cmd_strimzi292(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tekton292(int argc, char args[][CMD_MAX_LEN]);
static void cmd_concourse292(int argc, char args[][CMD_MAX_LEN]);
static void cmd_spinnaker292(int argc, char args[][CMD_MAX_LEN]);
"""

b292_entries = """    /* Batch 292: More DevOps */
    {"argo-workflows", cmd_argo292_workflows}, {"event-routing", cmd_event292_routing}, {"knative", cmd_knative292},
    {"openfaas", cmd_openfaas292}, {"fission", cmd_fission292}, {"kubeless", cmd_kubeless292},
    {"camel", cmd_camel292}, {"camel-k", cmd_camel292_k}, {"strimzi", cmd_strimzi292},
    {"tekton", cmd_tekton292}, {"concourse", cmd_concourse292}, {"spinnaker", cmd_spinnaker292},
"""

b292_funcs = """/* ===== Batch 292: More DevOps ===== */
static void cmd_argo292_workflows(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Argo Workflows: workflow engine\\n");
    vga_puts("argo: 3 workflows completed\\n");
}
static void cmd_event292_routing(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Event Routing: event-driven architecture\\n");
}
static void cmd_knative292(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Knative: serverless platform\\n");
    vga_puts("knative: 2 services, 5 revisions\\n");
}
static void cmd_openfaas292(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OpenFaaS: serverless functions\\n");
    vga_puts("openfaas: 10 functions deployed\\n");
}
static void cmd_fission292(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Fission: serverless framework\\n");
}
static void cmd_kubeless292(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Kubeless: Kubernetes-native serverless\\n");
}
static void cmd_camel292(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Apache Camel: integration framework\\n");
}
static void cmd_camel292_k(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Camel K: Kubernetes integration\\n");
}
static void cmd_strimzi292(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Strimzi: Kafka on Kubernetes\\n");
}
static void cmd_tekton292(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Tekton: Kubernetes-native CI/CD\\n");
}
static void cmd_concourse292(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Concourse: CI/CD pipeline\\n");
}
static void cmd_spinnaker292(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Spinnaker: continuous delivery platform\\n");
}
"""

# ===== BATCH 293: Cloud Native =====
b293_decls = """static void cmd_argo293_cd(int argc, char args[][CMD_MAX_LEN]);
static void cmd_argo293_events(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kyverno293(int argc, char args[][CMD_MAX_LEN]);
static void cmd_opa293(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gatekeeper293(int argc, char args[][CMD_MAX_LEN]);
static void cmd_crossplane293(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cdk8s293(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pulumi293(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cdk293(int argc, char args[][CMD_MAX_LEN]);
static void cmd_serverless293(int argc, char args[][CMD_MAX_LEN]);
static void cmd_wasm293(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ebpf293(int argc, char args[][CMD_MAX_LEN]);
"""

b293_entries = """    /* Batch 293: Cloud Native */
    {"argo-cd2", cmd_argo293_cd}, {"argo-events", cmd_argo293_events}, {"kyverno", cmd_kyverno293},
    {"opa", cmd_opa293}, {"gatekeeper", cmd_gatekeeper293}, {"crossplane", cmd_crossplane293},
    {"cdk8s", cmd_cdk8s293}, {"pulumi", cmd_pulumi293}, {"cdk2", cmd_cdk293},
    {"serverless", cmd_serverless293}, {"wasm", cmd_wasm293}, {"ebpf", cmd_ebpf293},
"""

b293_funcs = """/* ===== Batch 293: Cloud Native ===== */
static void cmd_argo293_cd(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ArgoCD: GitOps\\n");
}
static void cmd_argo293_events(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Argo Events: event-driven automation\\n");
}
static void cmd_kyverno293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Kyverno: Kubernetes policy engine\\n");
}
static void cmd_opa293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OPA: Open Policy Agent\\n");
}
static void cmd_gatekeeper293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Gatekeeper: admission controller\\n");
}
static void cmd_crossplane293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Crossplane: cloud infrastructure\\n");
}
static void cmd_cdk8s293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("cdk8s: Kubernetes app definition\\n");
}
static void cmd_pulumi293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Pulumi: infrastructure as code\\n");
}
static void cmd_cdk293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("AWS CDK: cloud development kit\\n");
}
static void cmd_serverless293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Serverless Framework\\n");
}
static void cmd_wasm293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("WebAssembly: binary instruction format\\n");
}
static void cmd_ebpf293(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("eBPF: extended Berkeley Packet Filter\\n");
}
"""

# ===== BATCH 294: More AI =====
b294_decls = """static void cmd_vllm294(int argc, char args[][CMD_MAX_LEN]);
static void cmd_text294_generation_inference(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ray294(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mlflow294(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kubeflow294(int argc, char args[][CMD_MAX_LEN]);
static void cmd_seldon294(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bentoml294(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ray294_serve(int argc, char args[][CMD_MAX_LEN]);
static void cmd_triton294(int argc, char args[][CMD_MAX_LEN]);
static void cmd_onnx294(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tensorrt294(int argc, char args[][CMD_MAX_LEN]);
static void cmd_core294ml(int argc, char args[][CMD_MAX_LEN]);
"""

b294_entries = """    /* Batch 294: AI Infrastructure */
    {"vllm", cmd_vllm294}, {"text-generation-inference", cmd_text294_generation_inference}, {"ray", cmd_ray294},
    {"mlflow", cmd_mlflow294}, {"kubeflow", cmd_kubeflow294}, {"seldon", cmd_seldon294},
    {"bentoml", cmd_bentoml294}, {"ray-serve", cmd_ray294_serve}, {"triton", cmd_triton294},
    {"onnx", cmd_onnx294}, {"tensorrt", cmd_tensorrt294}, {"coreml", cmd_core294ml},
"""

b294_funcs = """/* ===== Batch 294: AI Infrastructure ===== */
static void cmd_vllm294(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("vLLM: LLM serving engine\\n");
    vga_puts("vllm: serving on http://localhost:8000\\n");
}
static void cmd_text294_generation_inference(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Text Generation Inference\\n");
}
static void cmd_ray294(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Ray: distributed computing\\n");
    vga_puts("ray: 3 nodes, 12 cores\\n");
}
static void cmd_mlflow294(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("MLflow: ML lifecycle management\\n");
    vga_puts("mlflow: 5 experiments, 20 runs\\n");
}
static void cmd_kubeflow294(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Kubeflow: ML on Kubernetes\\n");
}
static void cmd_seldon294(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Seldon Core: model deployment\\n");
}
static void cmd_bentoml294(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BentoML: model serving\\n");
}
static void cmd_ray294_serve(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Ray Serve: scalable model serving\\n");
}
static void cmd_triton294(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Triton Inference Server\\n");
    vga_puts("triton: serving 3 models\\n");
}
static void cmd_onnx294(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ONNX Runtime: ML inference\\n");
}
static void cmd_tensorrt294(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("TensorRT: GPU inference optimizer\\n");
}
static void cmd_core294ml(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Core ML: Apple ML framework\\n");
}
"""

# Fix syntax errors
b292_decls = b292_decls.replace("static void_cmd_", "static void cmd_")
b294_decls = b294_decls.replace("static void cmd_text294_generation_inference", "static void cmd_text294_gen")

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b291_decls + b292_decls + b293_decls + b294_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b291_entries + b292_entries + b293_entries + b294_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b291_funcs + b292_funcs + b293_funcs + b294_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)

print("Injected Batches 291-294 (48 new commands)")