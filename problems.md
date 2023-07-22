export not working: but it frees the env
    "env" after export will segfault
    export then ^d (eof signal) will double free

cd breaks when only 1 args: should nevigate to previous dir

leaks when update env: should free all of env and copy the new one, or just free the ones updated.