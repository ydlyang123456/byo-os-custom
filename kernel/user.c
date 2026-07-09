/* BYO-OS - User Permission System */
#include <kernel.h>

#define MAX_USERS 8
#define MAX_GROUPS 4
#define MAX_NAME_LEN 32

typedef struct {
    int uid;
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    user_level_t level;
    int group;
    int active;
} user_t;

typedef struct {
    int gid;
    char name[MAX_NAME_LEN];
} group_t;

static user_t users[MAX_USERS];
static group_t groups[MAX_GROUPS];
static int current_uid = 0;
static int user_count = 0;

void user_init(void) {
    for (int i = 0; i < MAX_USERS; i++) users[i].active = 0;
    for (int i = 0; i < MAX_GROUPS; i++) groups[i].gid = -1;

    groups[0].gid = 0; strcpy(groups[0].name, "users");
    groups[1].gid = 1; strcpy(groups[1].name, "admins");

    user_create("root", "toor", USER_ROOT, 1);
    user_create("admin", "admin", USER_ADMIN, 1);
    user_create("guest", "guest", USER_GUEST, 0);
    current_uid = 0;
    serial_puts("[USER] Permission system initialized\n");
}

int user_create(const char* username, const char* password, user_level_t level, int group) {
    if (user_count >= MAX_USERS) return -1;
    for (int i = 0; i < user_count; i++) {
        if (users[i].active && strcmp(users[i].username, username) == 0) return -2;
    }
    int slot = user_count++;
    users[slot].uid = slot;
    strncpy(users[slot].username, username, MAX_NAME_LEN - 1);
    users[slot].username[MAX_NAME_LEN - 1] = '\0';
    strncpy(users[slot].password, password, MAX_NAME_LEN - 1);
    users[slot].password[MAX_NAME_LEN - 1] = '\0';
    users[slot].level = level;
    users[slot].group = group;
    users[slot].active = 1;
    return slot;
}

int user_login(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].active && strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            current_uid = users[i].uid;
            return users[i].uid;
        }
    }
    return -1;
}

void user_logout(void) { current_uid = 0; }
int user_get_uid(void) { return current_uid; }

const char* user_get_name(void) {
    for (int i = 0; i < user_count; i++)
        if (users[i].active && users[i].uid == current_uid) return users[i].username;
    return "unknown";
}

user_level_t user_get_level(void) {
    for (int i = 0; i < user_count; i++)
        if (users[i].active && users[i].uid == current_uid) return users[i].level;
    return USER_GUEST;
}

int user_has_permission(user_level_t required) { return user_get_level() >= required; }

void user_list_users(char* output, uint32_t max_len) {
    output[0] = '\0';
    uint32_t pos = 0;
    const char* ln[] = {"guest", "user", "admin", "root"};
    for (int i = 0; i < user_count; i++) {
        if (!users[i].active) continue;
        uint32_t nl = strlen(users[i].username);
        uint32_t ll = strlen(ln[users[i].level]);
        if (pos + nl + ll + 8 < max_len) {
            memcpy(output + pos, users[i].username, nl); pos += nl;
            output[pos++] = ' '; output[pos++] = '(';
            memcpy(output + pos, ln[users[i].level], ll); pos += ll;
            output[pos++] = ')'; output[pos++] = '\n';
        }
    }
    output[pos] = '\0';
}