/* BYO-OS User - x86_64 */
#include <kernel.h>
static int current_uid = 0;
static const char* usernames[] = {"root","admin","guest"};
static user_level_t user_levels[] = {USER_ROOT, USER_ADMIN, USER_GUEST};
void user_init(void) { current_uid = 0; }
int user_create(const char* username, const char* password, user_level_t level, int group) {
    (void)username; (void)password; (void)level; (void)group; return 0;
}
int user_login(const char* username, const char* password) {
    (void)password;
    for (int i = 0; i < 3; i++) { int j = 0; while (usernames[i][j] == username[j] && username[j]) j++; if (!usernames[i][j] && !username[j]) { current_uid = i; return 0; } }
    return -1;
}
void user_logout(void) { current_uid = 0; }
int user_get_uid(void) { return current_uid; }
const char* user_get_name(void) { return usernames[current_uid]; }
user_level_t user_get_level(void) { return user_levels[current_uid]; }
int user_has_permission(user_level_t required) { return user_levels[current_uid] >= required; }
void user_list_users(char* output, uint32_t max_len) {
    snprintf(output, max_len, "root:0:3\nadmin:1:2\nguest:2:1\n");
}
int user_get_count(void) { return 3; }