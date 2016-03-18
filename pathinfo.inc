<?php
    //Consider a URL such as:
    //  http://example.com/scriptname/var1=val1/var2=val2/path/to/filename.xyz
    //Transform it into:
    //  $PATH = '/path/to/filename.xyz'
    //    $PATH_VARS['var1'] = 'val1';
    //    $PATH_VARS['var2'] = 'val2';
    $PATH = '';
    $parts = explode('/', $_SERVER['PATH_INFO']);
    foreach ($parts as $part){
        $pieces = explode('=', $part);
        switch(count($pieces)){
            case 1: /* tack it on as part of a pathname */
                //Also ignore the leading '/' of PATH_INFO which turns into an empty '' from explode()
                if ($pieces[0] !== '') $PATH .= "/" . $pieces[0];
            break;
            default: /* Set up something like $_GET only with $PATH_VARS */
                $var = $pieces[0];
                // value might have = within it...
                unset($pieces[0]);
                $val = implode('=', $pieces);
                $PATH_VARS[$var] = $val;
            break;
        }
    }
?>
