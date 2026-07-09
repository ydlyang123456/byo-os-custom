$filePath = "E:\aisystem\byo-os\kernel\shell.c"
$content = [System.IO.File]::ReadAllText($filePath)

# --- INSERTION 1: Forward declarations after home_automation_120 forward declaration ---
$fwdDecl = @"
/* Batch 122: DevOps Toolchain Enhancement Commands */
static void argocd_sync_122(int argc, char args[][CMD_MAX_LEN]);
static void tekton_pipeline_122(int argc, char args[][CMD_MAX_LEN]);
static void flux_deploy_122(int argc, char args[][CMD_MAX_LEN]);
static void crossplane_manage_122(int argc, char args[][CMD_MAX_LEN]);
static void opa_evaluate_122(int argc, char args[][CMD_MAX_LEN]);
static void vault_manage_122(int argc, char args[][CMD_MAX_LEN]);
static void consul_service_122(int argc, char args[][CMD_MAX_LEN]);
static void nomad_job_122(int argc, char args[][CMD_MAX_LEN]);
static void boundary_access_122(int argc, char args[][CMD_MAX_LEN]);
static void waypoint_deploy_122(int argc, char args[][CMD_MAX_LEN]);
static void packer_image_122(int argc, char args[][CMD_MAX_LEN]);
static void sentinel_policy_122(int argc, char args[][CMD_MAX_LEN]);
"@

$searchFwd = "static void home_automation_120(int argc, char args[][CMD_MAX_LEN]);`r`n`r`nstatic const cmd_entry commands[]"
$replaceFwd = "static void home_automation_120(int argc, char args[][CMD_MAX_LEN]);`r`n" + $fwdDecl + "`r`nstatic const cmd_entry commands[]"
$content = $content.Replace($searchFwd, $replaceFwd)

# --- INSERTION 2: Command table entries ---
$searchCmd = '{"home-automation", home_automation_120},`r`n};'
$replaceCmd = @"
{"home-automation", home_automation_120},
    /* Batch 122: DevOps Toolchain Enhancement */
    {"argocd-sync", argocd_sync_122}, {"tekton-pipeline", tekton_pipeline_122}, {"flux-deploy", flux_deploy_122},
    {"crossplane-manage", crossplane_manage_122}, {"opa-evaluate", opa_evaluate_122}, {"vault-manage", vault_manage_122},
    {"consul-service", consul_service_122}, {"nomad-job", nomad_job_122}, {"boundary-access", boundary_access_122},
    {"waypoint-deploy", waypoint_deploy_122}, {"packer-image", packer_image_122}, {"sentinel-policy", sentinel_policy_122},
};
"@
$content = $content.Replace($searchCmd, $replaceCmd)

# --- INSERTION 3: Function implementations before shell_run ---
$funcImpl = Get-Content "E:\aisystem\byo-os\kernel\batch122_funcs.txt" -Raw
$searchShell = "void shell_run(void) {"
$replaceShell = $funcImpl + "`r`nvoid shell_run(void) {"
$content = $content.Replace($searchShell, $replaceShell)

[System.IO.File]::WriteAllText($filePath, $content)
Write-Output "Done. File updated."
