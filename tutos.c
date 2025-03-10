WIFEXITED(status) : Vérifie si le processus s'est terminé normalement.
WEXITSTATUS(status) : Récupère le code de sortie du processus si WIFEXITED est vrai.
WIFSIGNALED(status) : Vérifie si le processus a été terminé par un signal.
WTERMSIG(status) : Récupère le signal qui a tué le processus si WIFSIGNALED est vrai.
WIFSTOPPED(status) : Vérifie si le processus est arrêté.
WSTOPSIG(status) : Récupère le signal qui a arrêté le processus si WIFSTOPPED est vrai.
WNOHANG : Option pour waitpid pour ne pas bloquer si aucun enfant n'est terminé.