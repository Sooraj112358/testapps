#!/bin/bash

# @file
#
# @brief
#   This script proposes some facilities using repo. It has to be sourced.

# @ingroup IOT
# @author  Thamin C
# @date    19/03/2019
# COPYRIGHT:
#   Copyright (c) 2019 SmarDTV Global

#------------------------------------------------------------------------------

if [[ $_ == $0 ]]; then
  echo "This script must be sourced"
  exit 1
fi

##################################################################################
# Coloring messages
#################################################################################

msg_color()
{
  case $1 in
    "r"|"red")
      COLOR="\e[91m"
      ;;
    "g"|"green")
      COLOR="\e[92m"
      ;;
    "y"|"yellow")
      COLOR="\e[93m"
      ;;
    "b"|"blue")
      COLOR="\e[94m"
      ;;
    "m"|"magenta")
      COLOR="\e[95m"
      ;;
    "c"|"cyan")
      COLOR="\e[96m"
      ;;
  esac

  shift

  echo -e "$COLOR""$*""\e[39m"

}

msg_red()
{
  msg_color red "$*"
}

msg_green()
{
  msg_color green "$*"
}

msg_yellow()
{
  msg_color yellow "$*"
}

msg_blue()
{
  msg_color blue "$*"
}

msg_magenta()
{
  msg_color magenta "$*"
}

msg_cyan()
{
  msg_color cyan "$*"
}

msg_dbg()
{
  msg_green "$*"
}

msg()
{
  echo -e "$*"
}

srun()
{
  msg_blue "$*"
  msg "PATH : $PATH"
  time $*
  return $?
}


###############################################################################
# Deleting directories in background
###############################################################################

sbs_background_rm_dir()
{
  local dir_del=$1
  local tmp_empty_dir=""
  if [ ! -e "$dir_del" ]; then
    msg_red "$dir_del is not present. sbs_background_rm_dir failed."
    return 1
  fi

  if [ ! -d "$dir_del" ]; then
    msg_red "$dir_del is not directory. sbs_background_rm_dir failed."
    return 1
  fi

  msg_yellow "Bakground task : rm -rf $dir_del."

  tmp_empty_dir=$(dirname $dir_del)/$(mktemp -u | xargs basename)
  mv $dir_del $tmp_empty_dir
  rm -rf $tmp_empty_dir&
}

#------------------------------------------------------------------------------
msg_green "sbs_misc.sh was loaded."
