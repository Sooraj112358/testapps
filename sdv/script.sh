#!/bin/bash
SCRIPT_PATH=$(dirname "$(realpath "$0")")
${SCRIPT_PATH}/myecho ${SCRIPT_PATH} script-arg
