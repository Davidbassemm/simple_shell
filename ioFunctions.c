// Simplified Code with Changed Function Names

#include "shell.h"

char *custom_get_history_file(info_t *info) {
    char *directory = custom_getenv(info, "HOME=");
    if (!directory) {
        return NULL;
    }

    char *filename = custom_malloc(sizeof(char) * (custom_strlen(directory) + custom_strlen(HIST_FILE) + 2));
    if (!filename) {
        return NULL;
    }

    filename[0] = '\0';
    custom_strcpy(filename, directory);
    custom_strcat(filename, "/");
    custom_strcat(filename, HIST_FILE);

    return filename;
}

int custom_write_history(info_t *info) {
    ssize_t fd;
    char *filename = custom_get_history_file(info);
    list_t *node = NULL;

    if (!filename) {
        return -1;
    }

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    custom_free(filename);

    if (fd == -1) {
        return -1;
    }

    for (node = info->history; node; node = node->next) {
        custom_putsfd(node->str, fd);
        custom_putfd('\n', fd);
    }

    custom_putfd(BUF_FLUSH, fd);
    close(fd);

    return 1;
}

int custom_read_history(info_t *info) {
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = custom_get_history_file(info);

    if (!filename) {
        return 0;
    }

    fd = open(filename, O_RDONLY);
    custom_free(filename);

    if (fd == -1) {
        return 0;
    }

    if (!fstat(fd, &st)) {
        fsize = st.st_size;
    }

    if (fsize < 2) {
        return 0;
    }

    buf = custom_malloc(sizeof(char) * (fsize + 1));
    if (!buf) {
        return 0;
    }

    rdlen = read(fd, buf, fsize);
    buf[fsize] = '\0';

    if (rdlen <= 0) {
        return custom_free(buf), 0;
    }

    close(fd);

    for (i = 0; i < fsize; i++) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            custom_build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i) {
        custom_build_history_list(info, buf + last, linecount++);
    }

    custom_free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX) {
        custom_delete_node_at_index(&(info->history), 0);
    }

    custom_renumber_history(info);

    return info->histcount;
}

int custom_build_history_list(info_t *info, char *buf, int linecount) {
    list_t *node = NULL;

    if (info->history) {
        node = info->history;
    }

    custom_add_node_end(&node, buf, linecount);

    if (!info->history) {
        info->history = node;
    }

    return 0;
}

int custom_renumber_history(info_t *info) {
    list_t *node = info->history;
    int i = 0;

    while (node) {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}

