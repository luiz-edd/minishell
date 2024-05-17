#!/usr/bin/env python3

import subprocess
import os

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
colours = [GREEN, RED, COLOR_LIMITER]

user = os.environ['USER']

# INPUT REFERENCE LIST
input_list = ["echo hi | cat -e > outfile1 && < infile1 | cat -e && < infile2 cat"] #1
input_list.append("echo hi | cat -e > outfile1 && < infile1 | cat -e && < infile2 cat") #2
input_list.append("< infile1 cat") #3
input_list.append("echo hi") #4
input_list.append("echo hi | cat -e > outfile1 && < infile1 | cat -e") #5
input_list.append("dsfasdf || echo hello | cat -e && echo bye || echo kitty") #6
input_list.append("echo oi && ech oi2 | echo oi3 | echo oi4 || echo oi5") #7
input_list.append("ech oi && echo hi | echo hello | echo bonjour || echo haha") #8
input_list.append("echo oi || echo hi && echo hello && echo bonjour || echo haha") #9
input_list.append("ech && echo oi || echo hey") #10
input_list.append("ech oi || echo oi && echo hi | cat -e") #11
input_list.append("echo hello | cat -e && ls | wc -l") #12
input_list.append("echo hi > infile1 && echo bye > infile2") #13
input_list.append("echo hi | cat -e > outfile1 && < infile1 | cat -e && < infile2 cat") #14
input_list.append("< infile1 cat") #15
input_list.append("< infile1 cat | echo") #16
input_list.append("echo hi | cat -e > outfile1 && < infile1 | cat -e") #17
input_list.append("cat outfile1") #18
input_list.append("cat > .") #19
input_list.append("cat > /") #20
input_list.append("cat > usr/local/bin") #21
input_list.append("cat > /usr/local/bin") #22
input_list.append("cat > \"\"") #23
input_list.append("cat > ''") #24
input_list.append("echo bye > \" \"") #25
input_list.append("cat < \" \"") #26
input_list.append("echo hi > ' '") #27
input_list.append("cat < ' '") #28
input_list.append("echo hello > \"fdasdfsa\"") #29
input_list.append("cat < \"fdasdfsa\"") #30
input_list.append("echo kitty > \"\"fdasdfsa\"\"") #31
input_list.append("cat < \"\"fdasdfsa\"\"") #32
input_list.append("cat < .") #33
input_list.append("cat < /") #34
input_list.append("cat < usr/local/bin") #35
input_list.append("cat < /usr/local/bin") #36
input_list.append("cat < \"\"") #37
input_list.append("cat < ''") #38
input_list.append("cat < \" \"") #39
input_list.append("cat < ' '") #40
input_list.append("cat < \"fdasdfsa\"") #41
input_list.append("cat < \"\"fdasdfsa\"\"") #42
input_list.append("echo hi > .") #43
input_list.append("echo hi > /") #44
input_list.append("echo hi > usr/local/bin") #45
input_list.append("echo hi > /usr/local/bin") #46
input_list.append("echo hi > \"\"") #47
input_list.append("echo hi > ''") #48
input_list.append("echo hi > \" \"") #49
input_list.append("cat < \" \"") #50
input_list.append("echo bye > ' '") #51
input_list.append("cat < ' '") #52
input_list.append("echo hi < .") #53
input_list.append("echo hi < /") #54
input_list.append("echo hi < usr/local/bin") #55
input_list.append("echo hi < /usr/local/bin") #56
input_list.append("echo hi < \"\"") #57
input_list.append("echo hi < ''") #58
input_list.append("echo hi < \" \"") #59
input_list.append("echo hi < ' '") #60
input_list.append("export var=usr/local/bin var01=filename && cat > $var") #61
input_list.append("export var01=filename && cat infile1 > \"\"$var01\"\"") #62
input_list.append("export var01=filename && cat \"\"$var01\"\"") #63
input_list.append("cat > \"\"$vor\"\"") #64
input_list.append("cat > $vor") #65
input_list.append("echo $\"\" USER") #66
input_list.append("echo $\"\" USER \"\"") #67
input_list.append("echo $\"\"\"                 \" USER \"\" hi") #68
input_list.append("echo $\"\"\"\"\"\"\"\"\"\"\"\" USER \"\" hey") #69
input_list.append("echo $\"\"\"\" USER \"\" a") #70
input_list.append("echo $\"\"'' USER \"\" b") #71
input_list.append("echo $'' USER \"\"c") #72
input_list.append("echo $'''' USER \"\"d") #73
input_list.append("echo $' ' '' USER \"\" e") #74
input_list.append("echo $' '\"\" USER \"\" f") #75
input_list.append("echo $\"''\" USER \"\"g") #76
input_list.append("echo $'''' USER \"\" h") #77
input_list.append("echo $  \"''\" USER \"\" i") #78
input_list.append("echo $  \"\"\"\" USER \"\" j") #79
input_list.append("echo $  \"\" USER") #80
input_list.append("echo \"        $USER   \" k") #81
input_list.append("echo $") #82
input_list.append("echo $$") #83
input_list.append("echo $$$") #84
input_list.append("$") #85
input_list.append("$$") #86
input_list.append("$$$") #87
input_list.append("export carol=55 && echo $carol") #88
input_list.append("export carol=55 && echo \"carol\"") #89
input_list.append("export carol=55 && echo $\"carol\"") #90
input_list.append("export carol=55 && echo \"$carol\"") #91
input_list.append("export carol=55 && echo '$carol'") #92
input_list.append("export carol=55 && echo $carolbia$") #93
input_list.append("export carol=55 && echo $carolbia$ hi") #94
input_list.append("export carol=55 && echo $carol$?bia$ hi") #95
input_list.append("export carol=55 && $'carol'$'bia'$ ") #96
input_list.append("export carol=55 && echo $\"carol\"$\"bia\"$") #97
input_list.append("export carol=55 && $'carol''bia'") #98
input_list.append("export carol=55 && $\"carol\"\"bia\"") #99
input_list.append("export carol=55 && echo $carolbia$ | cat -e > outfile3 && echo bye") #100
input_list.append("export carol=55 var=\"o hello\" var50=\"abc      def\" && ech$var") #101
input_list.append("export carol=55 var=\"o hello\" var50=\"abc      def\" && echo $var50") #102
input_list.append("echo $adfasfsd") #103
input_list.append("$adfasfsd") #104
input_list.append("$%342342") #105
input_list.append("$\"342342") #106
input_list.append("export \"\"") #107
input_list.append("export var30 && export | grep var30") #108
input_list.append("export var30 && export var30=carol && export | grep var30") #109
input_list.append("export var20=bia && export | grep var20") #110
input_list.append("export var20=bia && export var20 && export | grep var20") #111
input_list.append("export var=variable && export $var=carol && export | grep $var") #112
input_list.append("export var40=oi var50=hi && export var= && export | grep var=\"\"") #113
input_list.append("export var= && export var=20 && export | grep var=") #114
input_list.append("export var=20 && export var= && export | grep var=") #115
input_list.append("export var70 && export | grep var70") #116
input_list.append("export var10 && export var100 && export | grep var10") #117
input_list.append("export \" \"") #118
input_list.append("export ''") #119
input_list.append("export ' '") #120
input_list.append("export var=variable && export $var=$USER && export | grep variable=") #121
input_list.append("export var=oi | echo hey") #122
input_list.append("unset \"\"") #123
input_list.append("export var=variable && export $var=123") #124
input_list.append("export var20=carol && export | grep var20") #125
input_list.append("export var30 && export | grep var30") #126
input_list.append("export var40= && export | grep var40") #127
input_list.append("export carol=55 && $USER$carol") #128
input_list.append("export carol=55 && export var=variable && $USER$var") #129
input_list.append("oitudobem") #130
input_list.append("$USERoi") #131
input_list.append("$USER'") #132
input_list.append("\"$USER\"") #133
input_list.append("'$USER'") #134
input_list.append("\"$USER'") #135
input_list.append("$") #136
input_list.append("$$") #137
input_list.append("$$$") #138
input_list.append("echo oi > tudo bem") #139
input_list.append("cat tudo") #140
input_list.append("< infile1 cat | echo hey") #141
input_list.append("echo hey | < infile1 cat") #142
input_list.append("whoami | < infile1 cat") #143
input_list.append("rm infile1") #144
input_list.append("echo hey | < infile1 cat") #145
input_list.append("whoami | < infile1 cat") #146
input_list.append("echo hi | (echo hello | cat -e)") #147
input_list.append("echo hi | (echo hello && echo bye) | cat -e") #148
input_list.append("(export var=carol) && export | grep var=") #149
input_list.append("(ech hi || echo carol > outfile1 && echo bia) | cat -e && echo bye") #150
input_list.append("(ech hi || (echo carol > outfile1 && echo bia)) | cat -e && echo bye") #151
input_list.append("(ech hi || (echo carol > outfile1  | echo bia)) | cat -e && echo bye") #152
input_list.append("(echo bye) echo hi ) (ls (echo hi)") #153
input_list.append("(echo bye)) ((echo hi)") #154
input_list.append("((echo hi | cat -e) | cat -e)") #155 
input_list.append("echo \"(hello)\" > infile1") #156
input_list.append("cat infile1 | grep \");\"$") #157
input_list.append("cat infile1 | grep \"(\"") #158
input_list.append("Error") #159

# OUTPUT REFERENCE LIST
output_ref_list = ["infile1: No such file or directory\ninfile2: No such file or directory\n"] #1
output_ref_list.append("infile1: No such file or directory\ninfile2: No such file or directory\n") #2
output_ref_list.append("infile1: No such file or directory\n") #3
output_ref_list.append("hi\n") #4
output_ref_list.append("infile1: No such file or directory\n") #5
output_ref_list.append("dsfasdf: command not found\nhello$\nbye\n") #6
output_ref_list.append("oi\noi4\nech: command not found\n") #7
output_ref_list.append("ech: command not found\nhaha\n") #8
output_ref_list.append("oi\nhello\nbonjour\n") #9
output_ref_list.append("ech: command not found\nhey\n") #10
output_ref_list.append("ech: command not found\noi\nhi$\n") #11
output_ref_list.append("hello$\n14\n") #12
output_ref_list.append("") #13
output_ref_list.append("bye\n") #14
output_ref_list.append("hi\n") #15 
output_ref_list.append("\n") #16
output_ref_list.append("") #17
output_ref_list.append("hi$\n") #18
output_ref_list.append(".: Is a directory\n") #19
output_ref_list.append("/: Is a directory\n") #20
output_ref_list.append("usr/local/bin: No such file or directory\n") #21
output_ref_list.append("/usr/local/bin: Is a directory\n") #22
output_ref_list.append(" : No such file or directory\n") #23
output_ref_list.append(" : No such file or directory\n") #24
output_ref_list.append("") #25
output_ref_list.append("bye\n") #26
output_ref_list.append("") #27
output_ref_list.append("hi\n") #28
output_ref_list.append("") #29
output_ref_list.append("hello\n") #30
output_ref_list.append("") #31
output_ref_list.append("kitty\n") #32
output_ref_list.append("cat: -: Is a directory\n") #33
output_ref_list.append("cat: -: Is a directory\n") #34
output_ref_list.append("usr/local/bin: No such file or directory\n") #35
output_ref_list.append("cat: -: Is a directory\n") #36
output_ref_list.append(" : No such file or directory\n") #37
output_ref_list.append(" : No such file or directory\n") #38
output_ref_list.append("hi\n") #39
output_ref_list.append("hi\n") #40
output_ref_list.append("kitty\n") #41
output_ref_list.append("kitty\n") #42
output_ref_list.append(".: Is a directory\n") #43
output_ref_list.append("/: Is a directory\n") #44
output_ref_list.append("usr/local/bin: No such file or directory\n") #45
output_ref_list.append("/usr/local/bin: Is a directory\n") #46
output_ref_list.append(" : No such file or directory\n") #47
output_ref_list.append(" : No such file or directory\n") #48
output_ref_list.append("") #49
output_ref_list.append("hi\n") #50
output_ref_list.append("") #51
output_ref_list.append("bye\n") #52
output_ref_list.append("hi\n") #53
output_ref_list.append("hi\n") #54
output_ref_list.append("usr/local/bin: No such file or directory\n") #55
output_ref_list.append("hi\n") #56
output_ref_list.append(" : No such file or directory\n") #57
output_ref_list.append(" : No such file or directory\n") #58
output_ref_list.append("hi\n") #59
output_ref_list.append("hi\n") #60
output_ref_list.append("usr/local/bin: No such file or directory\n") #61
output_ref_list.append("") #62
output_ref_list.append("hi\n") #63
output_ref_list.append(" : No such file or directory\n") #64
output_ref_list.append("ambiguous redirect\n") #65
output_ref_list.append(" USER\n") #66
output_ref_list.append(" USER \n") #67
output_ref_list.append("                  USER  hi\n") #68
output_ref_list.append(" USER  hey\n") #69
output_ref_list.append(" USER  a\n") #70
output_ref_list.append(" USER  b\n") #71
output_ref_list.append(" USER c\n") #73
output_ref_list.append(" USER d\n") #73
output_ref_list.append("   USER  e\n") #74
output_ref_list.append("  USER  f\n") #75
output_ref_list.append("'' USER g\n") #76
output_ref_list.append(" USER  h\n") #77
output_ref_list.append("$ '' USER  i\n") #78
output_ref_list.append("$  USER  j\n") #79
output_ref_list.append("$  USER\n") #80
output_ref_list.append(f"        {user}    k\n") #81
output_ref_list.append("$\n") #82
output_ref_list.append("$$\n") #83
output_ref_list.append("$$$\n") #84
output_ref_list.append("$: command not found\n") #85
output_ref_list.append("$$: command not found\n") #86
output_ref_list.append("$$$: command not found\n") #87
output_ref_list.append("55\n") #88
output_ref_list.append("carol\n") #89
output_ref_list.append("carol\n") #90
output_ref_list.append("55\n") #91
output_ref_list.append("$carol\n") #92
output_ref_list.append("$\n") #93
output_ref_list.append("$ hi\n") #94
output_ref_list.append("550bia$ hi\n") #95
output_ref_list.append("carolbia$: command not found\n") #96
output_ref_list.append("carolbia$\n") #97
output_ref_list.append("carolbia: command not found\n") #98
output_ref_list.append("carolbia: command not found\n") #19
output_ref_list.append("bye\n") #100
output_ref_list.append("hello\n") #101
output_ref_list.append("abc def\n") #102
output_ref_list.append("\n") #103
output_ref_list.append("") #104
output_ref_list.append("$%342342: command not found\n") #105
output_ref_list.append("Syntax error\n") #106
output_ref_list.append("export: not a valid identifier\n") #107
output_ref_list.append("declare -x var30\n") #108
output_ref_list.append("declare -x var30=\"carol\"\n") #109
output_ref_list.append("declare -x var20=\"bia\"\n") #110
output_ref_list.append("declare -x var20=\"bia\"\n") #111
output_ref_list.append("declare -x var=\"variable\"\ndeclare -x variable=\"carol\"\n") #112
output_ref_list.append("declare -x var=\"\"\n") #113
output_ref_list.append("declare -x var=\"20\"\n") #114
output_ref_list.append("declare -x var=\"\"\n") #115
output_ref_list.append("declare -x var70\n") #116
output_ref_list.append("declare -x var10\ndeclare -x var100\n") #117
output_ref_list.append("export: not a valid identifier\n") #118
output_ref_list.append("export: not a valid identifier\n") #119
output_ref_list.append("export: not a valid identifier\n") #120
output_ref_list.append(f"declare -x variable=\"{user}\"\n") #121
output_ref_list.append("hey\n") #122
output_ref_list.append("unset: not a valid identifier\n") #123
output_ref_list.append("") #124
output_ref_list.append("declare -x var20=\"carol\"\n") #125
output_ref_list.append("declare -x var30\n") #126
output_ref_list.append("declare -x var40=\"\"\n") #127
output_ref_list.append(f"{user}55: command not found\n") #128
output_ref_list.append(f"{user}variable: command not found\n") #129
output_ref_list.append("oitudobem: command not found\n") #130
output_ref_list.append("") #131
output_ref_list.append("Syntax error\n") #132
output_ref_list.append(f"{user}: command not found\n") #133
output_ref_list.append("$USER: command not found\n") #134
output_ref_list.append("Syntax error\n") #135
output_ref_list.append("$: command not found\n") #136
output_ref_list.append("$$: command not found\n") #137
output_ref_list.append("$$$: command not found\n") #138
output_ref_list.append("") #139
output_ref_list.append("oi bem\n") #140
output_ref_list.append("hey\n") #141
output_ref_list.append("hi\n") #142
output_ref_list.append("hi\n") #143
output_ref_list.append("") #144
output_ref_list.append("infile1: No such file or directory\n") #145
output_ref_list.append("infile1: No such file or directory\n") #146
output_ref_list.append("hello$\n") #147
output_ref_list.append("hello$\nbye$\n") #148
output_ref_list.append("") #149
output_ref_list.append("ech: command not found\nbia$\nbye\n") #150
output_ref_list.append("ech: command not found\nbia$\nbye\n") #151
output_ref_list.append("ech: command not found\nbia$\nbye\n") #152
output_ref_list.append("Syntax error\n") #153
output_ref_list.append("Syntax error\n") #154
output_ref_list.append("hi$$\n") #155
output_ref_list.append("") #156
output_ref_list.append("") #157
output_ref_list.append("(hello)\n") #158
output_ref_list.append("Error\n") #159

# OUTPUT EXIT CODE LIST
output_exit_code = ["1\n"] #1
output_exit_code.append("1\n") #2
output_exit_code.append("1\n") #3
output_exit_code.append("0\n") #4
output_exit_code.append("0\n") #5
output_exit_code.append("0\n") #6
output_exit_code.append("0\n") #7
output_exit_code.append("0\n") #8
output_exit_code.append("0\n") #9
output_exit_code.append("0\n") #10
output_exit_code.append("0\n") #11
output_exit_code.append("0\n") #12
output_exit_code.append("0\n") #13
output_exit_code.append("0\n") #14
output_exit_code.append("0\n") #15
output_exit_code.append("0\n") #16
output_exit_code.append("0\n") #17
output_exit_code.append("0\n") #18
output_exit_code.append("1\n") #19
output_exit_code.append("1\n") #20
output_exit_code.append("1\n") #21
output_exit_code.append("1\n") #22
output_exit_code.append("1\n") #23
output_exit_code.append("1\n") #24
output_exit_code.append("0\n") #25
output_exit_code.append("0\n") #26
output_exit_code.append("0\n") #27
output_exit_code.append("0\n") #28
output_exit_code.append("0\n") #29
output_exit_code.append("0\n") #30
output_exit_code.append("0\n") #31
output_exit_code.append("0\n") #32
output_exit_code.append("1\n") #33
output_exit_code.append("1\n") #34
output_exit_code.append("1\n") #35
output_exit_code.append("1\n") #36
output_exit_code.append("1\n") #37
output_exit_code.append("1\n") #38
output_exit_code.append("0\n") #39
output_exit_code.append("0\n") #40
output_exit_code.append("0\n") #41
output_exit_code.append("0\n") #42
output_exit_code.append("1\n") #43
output_exit_code.append("1\n") #44
output_exit_code.append("1\n") #45
output_exit_code.append("1\n") #46
output_exit_code.append("1\n") #47
output_exit_code.append("1\n") #48
output_exit_code.append("0\n") #49
output_exit_code.append("0\n") #50
output_exit_code.append("0\n") #51
output_exit_code.append("0\n") #52
output_exit_code.append("0\n") #53
output_exit_code.append("0\n") #54
output_exit_code.append("1\n") #55
output_exit_code.append("0\n") #56
output_exit_code.append("1\n") #57
output_exit_code.append("1\n") #58
output_exit_code.append("0\n") #59
output_exit_code.append("0\n") #60
output_exit_code.append("1\n") #61
output_exit_code.append("0\n") #62
output_exit_code.append("0\n") #63
output_exit_code.append("1\n") #64
output_exit_code.append("1\n") #65
output_exit_code.append("0\n") #66
output_exit_code.append("0\n") #67
output_exit_code.append("0\n") #68
output_exit_code.append("0\n") #69
output_exit_code.append("0\n") #70
output_exit_code.append("0\n") #71
output_exit_code.append("0\n") #72
output_exit_code.append("0\n") #73
output_exit_code.append("0\n") #74
output_exit_code.append("0\n") #75
output_exit_code.append("0\n") #76
output_exit_code.append("0\n") #77
output_exit_code.append("0\n") #78
output_exit_code.append("0\n") #79
output_exit_code.append("0\n") #80
output_exit_code.append("0\n") #81
output_exit_code.append("0\n") #82
output_exit_code.append("0\n") #83
output_exit_code.append("0\n") #84
output_exit_code.append("127\n") #85
output_exit_code.append("127\n") #86
output_exit_code.append("127\n") #87
output_exit_code.append("0\n") #88
output_exit_code.append("0\n") #89
output_exit_code.append("0\n") #90
output_exit_code.append("0\n") #91
output_exit_code.append("0\n") #92
output_exit_code.append("0\n") #93
output_exit_code.append("0\n") #94
output_exit_code.append("0\n") #95
output_exit_code.append("127\n") #96
output_exit_code.append("0\n") #97
output_exit_code.append("127\n") #98
output_exit_code.append("127\n") #99
output_exit_code.append("0\n") #100
output_exit_code.append("0\n") #101
output_exit_code.append("0\n") #102
output_exit_code.append("0\n") #103
output_exit_code.append("0\n") #104
output_exit_code.append("127\n") #105
output_exit_code.append("2\n") #106
output_exit_code.append("1\n") #107
output_exit_code.append("0\n") #108
output_exit_code.append("0\n") #109
output_exit_code.append("0\n") #110
output_exit_code.append("0\n") #111
output_exit_code.append("0\n") #112
output_exit_code.append("0\n") #113
output_exit_code.append("0\n") #114
output_exit_code.append("0\n") #115
output_exit_code.append("0\n") #116
output_exit_code.append("0\n") #117
output_exit_code.append("1\n") #118
output_exit_code.append("1\n") #119
output_exit_code.append("1\n") #120
output_exit_code.append("0\n") #121
output_exit_code.append("0\n") #122
output_exit_code.append("1\n") #123
output_exit_code.append("0\n") #124
output_exit_code.append("0\n") #125
output_exit_code.append("0\n") #126
output_exit_code.append("0\n") #127
output_exit_code.append("127\n") #128
output_exit_code.append("127\n") #129
output_exit_code.append("127\n") #130
output_exit_code.append("0\n") #131
output_exit_code.append("2\n") #132
output_exit_code.append("127\n") #133
output_exit_code.append("127\n") #134
output_exit_code.append("2\n") #135
output_exit_code.append("127\n") #136
output_exit_code.append("127\n") #137
output_exit_code.append("127\n") #138
output_exit_code.append("0\n") #139
output_exit_code.append("0\n") #140
output_exit_code.append("0\n") #141
output_exit_code.append("0\n") #142
output_exit_code.append("0\n") #143
output_exit_code.append("0\n") #144
output_exit_code.append("1\n") #145
output_exit_code.append("1\n") #146
output_exit_code.append("0\n") #147
output_exit_code.append("0\n") #148
output_exit_code.append("1\n") #149
output_exit_code.append("0\n") #150
output_exit_code.append("0\n") #151
output_exit_code.append("0\n") #152
output_exit_code.append("2\n") #153
output_exit_code.append("2\n") #154
output_exit_code.append("0\n") #155
output_exit_code.append("0\n") #156
output_exit_code.append("1\n") #157
output_exit_code.append("0\n") #158
output_exit_code.append("X\n") #159


# Function to process the file content and modify it
# def process_and_modify_file(filename):
#     lines = []
#     with open(filename, 'r+') as file:
#         for line in file:
#             if {prompt} in line:
#                 value = line.split({prompt})
#                 if value[0] != '':
#                     lines.append(value[0])
#             else:
#                 lines.append(line)
#         # lines.pop()
#     return lines

i = 1
for command, reference, reference_exit_code in zip(input_list, output_ref_list, output_exit_code):
    command_exit_code = "\necho $?"
    with open("file", "w") as file:
        file.write(command + command_exit_code)
    with open("ref_file", "w") as ref_file:
        ref_file.write(reference)
    with open("status_ref_file", "w") as status_ref_file:
        status_ref_file.write(reference_exit_code)
    output = subprocess.run("./script.sh", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

    if (output.stdout == '0\n'):
        print(f"{colours[0]}{i}/{len(input_list)}.\n	OK  {colours[2]}")
    else:
        print(f"{colours[1]}{i}/{len(input_list)}.\n	KO  {colours[2]}")
    valgrind_status = subprocess.run('./valgrind.sh', stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
    if (valgrind_status.stdout == '0\n'):
        print(f"{colours[0]}	MOK  {colours[2]}")
    else:
        print(f"{colours[1]}	MKO  {colours[2]}")
    status = subprocess.run("./status.sh", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
    if (status.stdout == '0\n'):
        print(f"{colours[0]}	EOK  {colours[2]}")
    else:
        print(f"{colours[1]}	EKO  {colours[2]}")
    with open("result", "r") as result_file:
        result_command = result_file.read()
    with open("status_result", "r") as status_result_file:
        status_result = status_result_file.readlines()[-1]
    with open("log_file", "a") as log_file:
        log_file.write(f"{i}.\ncommand:\n{command}\nexpected output:\n{reference}\noutput received:\n{result_command}\nexpected status: {reference_exit_code}\nstatus received: {status_result}\n\n")
    i = i + 1
file_paths = [" ", "filename", "fdasdfsa", "file", "infile1", "infile2", "outfile1", "tudo", "outfile3", "ref_file", "outfile", "result", "status_file", "status_outfile", "status_ref_file", "status_result", "valgrind.log"]
rm_command = ["rm", "-f"] + file_paths
subprocess.run(rm_command)	