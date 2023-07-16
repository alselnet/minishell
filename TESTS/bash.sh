#!/bin/bash

# Chemin vers le fichier cmds.txt
cmds_file="cmds.txt"

# Vérification si le fichier cmds.txt existe
if [ ! -f "$cmds_file" ]; then
  echo "Le fichier $cmds_file n'existe pas."
  exit 1
fi

# Lecture du fichier cmds.txt
while IFS= read -r command; do
  # Vérification si la ligne est vide ou un commentaire (commençant par #)
  if [[ -z "$command" || "$command" =~ ^[[:space:]]*# ]]; then
    continue
  fi

  # Affichage de la commande avant de l'exécuter
  echo "minishell\$ $command"

  # Exécution de la commande
  eval "$command"
done < "$cmds_file"