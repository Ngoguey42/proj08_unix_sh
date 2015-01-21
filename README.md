# Project #8 SH, Jan 2015
>>>>> #####A shell of my own.

#####sh1 grade ``(tbd/100)`` ``(tbd/118)*``
#####sh2 grade ``(tbd/100)`` ``(tbd/118)*``
#####sh3 grade ``(tbd/100)`` ``(tbd/118)*``
--------  -----------------------

This project is subdivided into 4 parts.
- [ ] sh1: Implement basic built-in commands, execute any command from PATH, etc...
- [ ] sh2: Handle those six operators: "**; | < << >> >**" Introduced in [[PIPEX project](https://github.com/Ngoguey42/proj07_unix_pipex)].
- [ ] sh3: Cursor position and keyboard control keys. Introduced in [ft_select project].
- [ ] 42sh: Group project.

<br><br>

sh1 Goals:
- [X] Display a prompt.
- [X] Execute any command from PATH.
- [ ] Full error handling without errno.
- [X] Built-ins: cd, setenv, unsetenv, env, exit.
- [X] Read commands through argv's -c option or stdin reading.

My sh1 additions:
- [ ] All env's options.
- [X] Tilde '~' + options ('~+', '~-').

sh2 Goals:
- [X] Semicolons ';'.
- [X] Pipes '|'.
- [X] In redirection '<'.
- [X] Here document '<<'.
- [X] Append out redirection '>>'.
- [X] Out redirection '>'.

My sh2 additions:
- [X] Arguments for 'in' redirection: '[digits]**<**{&digits|file}'
- [X] Arguments for 'here document' redirection: '[digits]**<<**keyword'
- [X] Arguments for 'out' redirections: '[digits|&]**>**{&digits|file}'
- [X] Arguments for 'append' redirections: '[digits]**>>**file'

![MiniShell](http://i.imgur.com/FZTcUdg.png)
<br><br><br><br><br><br>

```
All my C files blindly observes school's norm, it may often lead to odd or illogical syntaxes.
- [ ] Forbiden keywords: for, do, switch, goto.
- [ ] No more than 25 lines inside a function block.
- [ ] No more than 80 characters per lines.
- [ ] At most 5 functions per files.
- [ ] Only 1 declaration per line.
- [ ] No declaration and assignation on the same line.
- [ ] At most 1 assignation per line.
- [ ] No more than 4 parameters for a function.
- [ ] No nested ternary.
- [ ] Comments alowed at the top of the file.
```
```
*
- A grade of 85 was required to validate the project.
- A maximum grade of 118 was reachable.
- Second sessions are organised for failed projects.
```
