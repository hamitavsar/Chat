#include "utils.h"

char *mx_change_offensive_words(char *str) {
    char *words[29] = {"yarram","mk","aq","sus ananı sikerim","tatava yapma aq","amına korum","fuck", "slut", "prostitute", "блеать",  "сука", "соси",
                  "fuck", "dick", "amcık", "хуй", "sikik", "orosbu", "сука",
                  "orosbu çocu", "onun bunun evladı", "k*rt", "kahbe", "amk", "даун",
                  "fuck your self", "fuck you", "mal", "salak", };
    int indx;
    char *res = mx_string_copy(str);
    char *tmp;

    for(int i = 0; i < 28; i++) {
        indx = mx_get_substr_index(str, words[i]);
        if (indx != -2 && indx != -1) {
            tmp = mx_replace_substr(res, words[i], "****");
            free(res);
            res = tmp;
        }
    }
    return res;
}
