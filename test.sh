#!/usr/bin/expect -f

set timeout 1
set prompt "minishell$ "

# Chemin vers votre exécutable minishell
set minishell_path "./minishell"

# NOM DU FICHIER
set filename "test1.txt"

# Lancement du minishell
spawn $minishell_path

# Attente du prompt
expect -re $prompt

# Lecture du fichier cmds.txt
set file [open $filename r]
while {[gets $file command] != -1} {
	if {[string trim $command] eq ""} {
        continue
    }
    # Envoi de la commande
    send "$command\r"
    expect -re $prompt
}
close $file

# Fermeture du minishell
send "exit\r"
expect eof