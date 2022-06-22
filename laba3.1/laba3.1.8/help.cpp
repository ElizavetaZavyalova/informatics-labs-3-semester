#include "help.h"

class interpreter;

std::string tosistem(int num, const int& base) {
    bool negative = 0;
    if (num < 0) {
        negative = 1;
        num *= -1;
    }
    std::string str = "";
    do {
        char remains = num % base;
        (remains < 10) ? (remains += '0') : (remains = remains - 10 + 'A');
        str = remains + str; num /= base;
    } while (num != 0);
    if (negative) {
        str = '-' + str;
    }
    return str;
}

int fromsistem(std::string str, const int& base) {
    int num = 0;
    int i = 0;
    int r = 0;
    int negative = 1;
    if (str[0] == '-') {
        negative = -1;
        str.erase(0, 1);
    }
    int len = str.length();
    if (len == 0) {
        throw(std::exception("not correct number"));
    }
    while (i < len) {
        r = (isdigit(str[i]) ? (str[i] - '0') : (str[i] - 'A' + 10));
        if (r >= base || r < 0)
            throw(std::exception("not correct base"));

        num = num * base + r;
        i++;
    }
    return negative * num;
}

 

settings& operator>> (settings& potok, char& c) {
    c = potok.in.get();
    if (c == '#') {
        while (c != '\n' && c != -1) {
            c = potok.in.get();
        }
        c = potok.in.get();
    }
    if (c == '[' || c == ']') {
        throw("find ][ ");
    }
    return potok;
}
settings& operator<< (settings& potok, const char& c) {

    return potok;
}
settings& operator>> (settings& potok, std::map<std::string, std::string>& opiration) {

    char c = ' ';
    potok >> c;
    std::string action = "";
    std::string nickname = "";
    while (c != -1) {
        while (isspace(c) && c != -1) {
            potok >> c;
        }
        while (!isspace(c) && c != -1) {
            action = action + c;
            potok >> c;
        }
        while (isspace(c) && c != -1) {
            potok >> c;
        }
        if (action == "op()" || action == "()op" || action == "(op)()" || action == "()(op)") {
            opiration["op"] = action; action = "";
            continue;
        }
        if (action == "left=" || action == "right=") {
            opiration["hand"] = action; action = "";
            continue;
        }
        while (!isspace(c) && c != -1) {
            nickname = nickname + c;
            potok >> c;
        }
        while (isspace(c) && c != -1) {
            potok >> c;
        }
        if (opiration.find(action) == opiration.cend() || nickname == "") {
            throw(std::exception("not correct settings"));
        }
        else {
            opiration[action] = nickname;
            action = ""; nickname = "";
        }
    }
    return potok;
}

settings& operator<< (settings& potok, const std::map<std::string, std::string>& opiration) {
    potok.in.close();
    potok.out.open("C:\\jjj\\laba8saves.txt");
    for (auto it = opiration.cbegin(); it != opiration.cend(); it++)
    {
        if ((*it).first == "op" || (*it).first == "hand") {
            potok.out << (*it).second << "\n";
            continue;
        }
        potok.out << (*it).first << " " << (*it).second << "\n";
    }
    potok.out.close();
    return potok;
}

 
void interpreter::variablecreate(const int count) {
    for (int i = 0; i < count; i++) {
        if (variable.find(key[i]) == variable.cend()) {
            variable[key[i]] = 0;
        }
    }
}

void interpreter::remake() {

    for (int i = 0; i < 3; i++) {
        key[i] = "";
    }
    opiration = "";
    base = 0;
    num[0] = 0;
    num[1] = 0;
}
interpreter::interpreter(std::string set) {
    std::map<std::string, std::string> opiration{
        {"add", "add"}, {"mult", "mult"}, {"sub", "sub"}, {"pow", "pow"}, {"div", "div"},{"rem","rem"},
        {"xor","xor"}, {"input", "in"},{"output", "print"},{"=","="}, {"op","op()"}, {"hand","left="}
    };
    settings create(set);
    create >> opiration;
    create << opiration;
    maxlen += opiration["="].length();
    int len = 0;
    for (auto i = opiration.cbegin(); i != opiration.cend(); i++) {
        if (len < (*i).second.length())
            len = (*i).second.length();
    }
    maxlen += len;
    functionbinar[opiration["add"]] = [](int& first, int& second) {
        return first + second;
    };
    functionbinar[opiration["mult"]] = [](int& first, int& second) {
        return first * second;
    };
    functionbinar[opiration["sub"]] = [](int& first, int& second) {
        return first - second;
    };
    functionbinar[opiration["pow"]] = [](int& first, int& second) {
        return pow(first, second);
    };
    functionbinar[opiration["rem"]] = [](int& first, int& second) {
        if (second <= 0)
            throw("we cant make devision by zero");
        return first % second;
    };
    functionbinar[opiration["div"]] = [](const  int& first, const int& second) {
        if (second == 0)
            throw("we cant make devision by zero");
        return first / second;
    };
    functionbinar[opiration["xor"]] = [](const  int& first, const int& second) {
        return (first + second) % 2;
    };
    read = opiration["input"];
    write = opiration["output"];
    if (opiration["op"] == "op()") {
        syntax["doop2v"] = "#(\v,\v)";
        syntax["doop2n"] = "#(\n,\n)";
        syntax["doopvn"] = "#(\v,\n)";
        syntax["doopnv"] = "#(\n,\v)";
        syntax["write"] = opiration["output"] + "(\t)";
        syntax["read"] = opiration["input"] + "(\b)";
        syntax["doopw"] = opiration["output"] + "(\t,\b)";
        syntax["doopr"] = opiration["input"] + "(\t,\b)";
    }
    else if (opiration["op"] == "()op") {
        syntax["doop2v"] = "(\v,\v)#";
        syntax["doop2n"] = "(\n,\n)#";
        syntax["doopnv"] = "(\n,\v)#";
        syntax["doopvn"] = "(\v,\n)#";
      
        syntax["doopw"] = "(\t,\b)" + opiration["output"];
        syntax["doopr"] = "(\t,\b)" + opiration["input"];
        syntax["write"] = "(\t)" + opiration["output"];
        syntax["read"] = "(\b)" + opiration["input"];
    }
    else if (opiration["op"] == "()(op)") {
        syntax["doop2v"] = "\v # \v";
        syntax["doop2n"] = "\n # \n";
        syntax["doopvn"] = "\v # \n";
        syntax["doopw"] = "\t " + opiration["output"];
        syntax["doopw"] += " \n";
        syntax["doopr"] = "\t " + opiration["input"];
        syntax["doopr"] += " \n";
        syntax["doopnv"] = "\n # \v";
        unarnobinar = 1;
        syntax["write"] = "(\t)" + opiration["output"];
        syntax["read"] = "(\b)" + opiration["input"];
        


    }
    else if (opiration["op"] == "(op)()") {
        syntax["doop2v"] = "\v # \v";
        syntax["doop2n"] = "\n # \n";
        syntax["doopvn"] = "\v # \n";
        syntax["doopnv"] = "\n # \v";
        syntax["doopw"] = "\t "+ opiration["output"];
        syntax["doopw"] += " \n";
        syntax["doopr"] = "\t " + opiration["input"];
        syntax["doopr"] += " \n";
        unarnobinar = 1;
        syntax["write"] = opiration["output"] + "(\t)";
        syntax["read"] = opiration["input"] + "(\b)";
    }
    ruvn = opiration["="];
    opiration["="] = " " + opiration["="];
    opiration["="] = opiration["="] + " ";
    
    if (opiration["hand"] == "left=") {
        std::string per = "\t" + opiration["="];
        syntax["doop2v"] = per + syntax["doop2v"];
        syntax["doop2n"] = per + syntax["doop2n"];
        syntax["doopnv"] = per + syntax["doopnv"];
        syntax["doopvn"] = per + syntax["doopvn"];
         
        syntax["read"] = per + syntax["read"];
    }
    else if (opiration["hand"] == "right=") {
        std::string per = opiration["="] + "\t";
        syntax["doop2v"] = syntax["doop2v"] + per;
        syntax["doop2n"] = syntax["doop2n"] + per;
        syntax["doopnv"] = syntax["doopnv"] + per;
        syntax["doopvn"] = syntax["doopvn"] + per;
        syntax["read"] = syntax["read"] + per;
        

    }
    for (auto i = syntax.begin(); i != syntax.end(); i++) {
        (*i).second = (*i).second + ';';

    }
}

bool interpreter::iscorrect(const std::string comand) {
    int syn = 0; int ect = 0; int k = 1; remake(); int opsize = 0; int n = 0;
    while (ect < ection.length() && syn < syntax[comand].length()) {
        if (syntax[comand][syn] == '#') {
            opiration = opiration + ection[ect]; syn++; ect++;
            while ((ection[ect]) != syntax[comand][syn] && ect != ection.length()) {
                opiration = opiration + ection[ect]; ect++;
            }
        }
        else if (syntax[comand][syn] == '\v' && isalpha(ection[ect])) {
            opsize++;
            key[k] = key[k] + ection[ect];  syn++;  ect++;
            while (ect != ection.length() && opsize!=33 &&(ection[ect] == '_' || isalpha(ection[ect]) || isdigit(ection[ect]))) {
                key[k] = key[k] + ection[ect]; ect++; opsize++;
            } k++; opsize = 0;
        }
        else if (syntax[comand][syn] == '\t' && isalpha(ection[ect])) {
            opsize++;
            key[0] = key[0] + ection[ect];  syn++;  ect++;
            while (ect != ection.length() && opsize != 33 && (ection[ect] == '_' || isalpha(ection[ect]) || isdigit(ection[ect]))) {
                key[0] = key[0] + ection[ect]; ect++; opsize++;
            }opsize = 0;
        }
        else if (syntax[comand][syn] == '\n' && isdigit(ection[ect])) {
            syn++;
            while (isdigit(ection[ect]) && ect != ection.length()) {
                num[n] = num[n] * 10 + ection[ect] - '0'; ect++;

            }
            n++;
        }
        else if (syntax[comand][syn] == ',' && syntax[comand][syn + 1] == '\b') {
            syn++;
            if (ection[ect] == ',') {
                ect++;
                if (syntax[comand][syn] == '\b') {
                    syn++;
                    if (isdigit(ection[ect])) {
                        base = base * 10 + ection[ect] - '0'; ect++;
                        if (isdigit(ection[ect])) {
                            base = base * 10 + ection[ect] - '0'; ect++;
                        }
                    }
                }
            }
            else {
                syn++; base = 10;
            }
        }
        else if (syntax[comand][syn] == '\b') {
            syn++;
            if (isdigit(ection[ect])) {
                base = base * 10 + ection[ect] - '0'; ect++;
                if (isdigit(ection[ect])) {
                    base = base * 10 + ection[ect] - '0'; ect++;
                }
            }
            else {
                base = 10;
            }
        }
        else if (ection[ect] == syntax[comand][syn]) {
            ect++; syn++;
        }
        else
            return 0;
    }
    if (ect == ection.length() && syn == syntax[comand].length())
        return 1;
    else
        return 0;
}


reading& operator>> (reading& potok, char& c) {
    c = potok.in.get();
    int scobka = 0;
    while (c == '[' || c == ']' || c == -1||isspace(c)) {
        if (c == '[') {
            scobka++;
            while (scobka != 0) {
                c = potok.in.get();
                if (c == '[') {
                    scobka++;
                }
                else if (c == ']') {
                    scobka--;
                }
                if (scobka < 0 || c == -1) {
                    throw(std::exception("not correct []"));
                }
            }
            c = potok.in.get();
        }
        if (isspace(c)) {
            while (isspace(c) && c != -1) {
                c=potok.in.get();
            }
        }
    }
    return potok;
}

reading& operator>> (reading& potok, interpreter& str) {
    char c = ' ';
    potok >> c;
    str.ection = "";
    while (c != -1 && c != ';' && str.ection.length() != str.maxlen) {
        str.ection = str.ection + c;
        potok >> c;
    }
    if (c == ';')
    str.ection = str.ection + ';';
    int pos = str.ection.find(str.ruvn);
    std::string ect = " " + str.ruvn;
    ect += " ";
    if (pos != -1) {
        str.ection.replace(pos, str.ruvn.length(), ect);
    }
    if (str.unarnobinar) {
        for (auto i = str.functionbinar.cbegin(); i != str.functionbinar.cend(); i++) {
            pos = str.ection.find((*i).first);
            if (pos != -1) {
                std::string ect = " " + (*i).first;
                ect += " ";
                str.ection.replace(pos, (*i).first.length(), ect);
                break;
            }
        }
    }
    return potok;
}

void interpreter::parser(const std::string interpritatorname) {

    std::string numstr = "";
    try {
        reading potok(interpritatorname);

        potok >> *this;
        while (ection != "") {
            if (iscorrect("read")) {
                if (base < 2 || base>36)
                    throw(std::exception("no correct base"));
                std::cout << key[0] << " -> " << base << " = ";
                std::cin >> numstr;


                variable[key[0]] = fromsistem(numstr, base);  potok >> *this;
                continue;

            }
            else if (iscorrect("write")) {

                variablecreate(1);

                std::cout << key[0] << "=" << variable[key[0]] << '\n';  potok >> *this;
                continue;


            }
            if (unarnobinar) {

                int  pos = ection.find(write);
                if (pos != -1) {
                    std::string ect = " " + write;
                    ect =ect + " ";
                    ection.replace(pos, write.length(), ect);
                    
                }
                pos = ection.find(read);
                if (pos != -1) {
                    std::string ect = " " + read;
                    ect =ect + " ";
                    ection.replace(pos, read.length(), ect);
                    
                }
            }

            if (iscorrect("doopr")) {
                base = num[0];
                if (base < 2 || base>36)
                    throw(std::exception("no correct base"));
                std::cout << key[0] << " -> " << base << " = ";
                std::cin >> numstr;
                variable[key[0]] = fromsistem(numstr, base);
            }
            else if (iscorrect("doopw")) {
                base = num[0];
                if (base < 2 || base>36)
                    throw(std::exception("no correct base"));
                variablecreate(1);
                numstr = tosistem(variable[key[0]], base);
                std::cout << key[0] << " -> " << base << " = ";
                std::cout << numstr << '\n';

            }

            else if (iscorrect("doop2v")) {
                if (functionbinar.find(opiration) == functionbinar.cend())
                    throw(std::exception("nocorrect opiration"));
                variablecreate(3);
                variable[key[0]] = functionbinar[opiration](variable[key[1]], variable[key[2]]);

            }
            else if (iscorrect("doop2n")) {
                if (functionbinar.find(opiration) == functionbinar.cend())
                    throw(std::exception("nocorrect opiration"));
                variablecreate(3);
                variable[key[0]] = functionbinar[opiration](num[0], num[1]);

            }
            else if (iscorrect("doopvn")) {


                if (functionbinar.find(opiration) == functionbinar.cend())
                    throw(std::exception("nocorrect opiration"));

                variablecreate(3);
                variable[key[0]] = functionbinar[opiration](variable[key[1]], num[0]);


            }
            else if (iscorrect("doopnv")) {
                if (functionbinar.find(opiration) == functionbinar.cend())
                    throw(std::exception("nocorrect opiration"));
                variablecreate(3);
                variable[key[0]] = functionbinar[opiration](num[0], variable[key[1]]);

            }
            else
                throw(std::exception("not correct action"));
            potok >> *this;
        }
    }
    catch (std::exception& ex) {
        numstr = (ex.what());
        std::cout << numstr;
    }
}
