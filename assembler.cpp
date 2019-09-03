#include <bits/stdc++.h>
using namespace std;

map<string, char> hex_map;

void init_hex_map() {
    hex_map["0000"] = '0';
    hex_map["0001"] = '1';
    hex_map["0010"] = '2';
    hex_map["0011"] = '3';
    hex_map["0100"] = '4';
    hex_map["0101"] = '5';
    hex_map["0110"] = '6';
    hex_map["0111"] = '7';
    hex_map["1000"] = '8';
    hex_map["1001"] = '9';
    hex_map["1010"] = 'A';
    hex_map["1011"] = 'B';
    hex_map["1100"] = 'C';
    hex_map["1101"] = 'D';
    hex_map["1110"] = 'E';
    hex_map["1111"] = 'F';
}

int to_int(string str) {
    int res = 0;
    for (auto ch : str) {
        res = res * 10 + (ch - '0');
    }

    return res;
}

string to_binary_string(int num, int bit_cnt) {
    string res(bit_cnt, '0');
    for (int i = 0; i < bit_cnt; i++)
        res[i] = (num & (1<<i)) ? '1' : '0';

    return res;
}

string bin_to_hex(string s) {
    string ret = "";
    if((int) s.size() % 4) s = string(4 - (int) s.size() % 4, '0') + s;
    for(int i=0; i<(int) s.size(); i+=4) {
        string cur = s.substr(i, 4);
        ret += hex_map[cur];
    }
    return ret;
}

vector<string> parse_memreadwrite(string line, char delimiter = ' ') {
    vector<string> tokens;
    stringstream ss(line);
    string s;
    while(getline(ss, s, delimiter)) {
        tokens.push_back(s);
    }

    vector<string> ret;
    if(delimiter == ' ') {
        for(auto &s : tokens) {
            auto v = parse_memreadwrite(s, ',');
            for(auto &qq : v) ret.push_back(qq);
        }
    }
    else if(delimiter == ',') {
        for(auto &s : tokens) {
            auto v = parse_memreadwrite(s, '(');
            for(auto &qq : v) ret.push_back(qq);
        }
    }
    else if(delimiter == '(') {
        for(auto &s : tokens) {
            auto v = parse_memreadwrite(s, ')');
            for(auto &qq : v) ret.push_back(qq);
        }
    }
    else {
        ret = tokens;
    }
    return ret;
}

void format_output() {
    init_hex_map();

    ifstream in("output.hex");
    string s;
    vector<string> to_out;
    while(in >> s) {
        cerr << "Read " << s << "\n";
        to_out.push_back(bin_to_hex(s));
        to_out.back() += " ";
    }
    in.close();

    ofstream out("output.hex");
    out << "v2.0 raw\n";
    for(auto &qq : to_out) out << qq << "\n";
    out.close();
    return ;
}

int main() {

    ifstream input_file("input.asm");
    ofstream output_file("output.hex");

    map <string, string> register_addresses;
    register_addresses["$zero"] = "0000";
    register_addresses["$t0"] = "0001";
    register_addresses["$t1"] = "0010";
    register_addresses["$t2"] = "0011";
    register_addresses["$t3"] = "0100";
    register_addresses["$t4"] = "0101";
    register_addresses["$sp"] = "0110";

    // opcodes for the instructions given. directly copied from
    // https://docs.google.com/spreadsheets/d/1iy2FUBD6W091Ca9JFfKujjvvc-fJJyjdy1CKQeiufF4/edit
    map <string, string> inst_to_code;
    inst_to_code["add"] = "0000";
    inst_to_code["and"] = "0001";
    inst_to_code["ori"] = "0010";
    inst_to_code["nor"] = "0011";
    inst_to_code["andi"] = "0100";
    inst_to_code["sub"] = "0101";
    inst_to_code["sll"] = "0110";
    inst_to_code["srl"] = "0111";
    inst_to_code["sw"] = "1000";
    inst_to_code["bneq"] = "1001";
    inst_to_code["subi"] = "1010";
    inst_to_code["beq"] = "1011";
    inst_to_code["j"] = "1100";
    inst_to_code["addi"] = "1101";
    inst_to_code["lw"] = "1110";
    inst_to_code["or"] = "1111";

    string str;
    while (getline(input_file, str)) {

        stringstream ss(str);
        string opcode, rd, rs, rt;
        int immediate, shift_amount;

        ss >> opcode;

        if (opcode == "add" or opcode == "sub" or opcode == "and" or opcode == "or"  or opcode == "nor") {

            ss >> rd >> rs >> rt;
            rd.pop_back();
            rs.pop_back();

            cerr << opcode << " " << rd << " " << rs << " " << rt << endl;
            output_file << inst_to_code[opcode] << register_addresses[rs] << register_addresses[rt]
                        << register_addresses[rd] << "0000\n";

        } else if ( opcode == "addi" or opcode == "subi" or opcode == "andi" or opcode == "ori") {

            ss >> rs >> rt >> immediate;
            rs.pop_back();
            rt.pop_back();

            cerr << opcode << " " << rs << " " << rt << " " << immediate << endl;
            output_file << inst_to_code[opcode] << register_addresses[rs] << register_addresses[rt]
                        << to_binary_string(immediate, 8) << "\n";

        } else if (opcode == "sll" or opcode == "srl") {
            ss >> rd >> rt >> shift_amount;
            rd.pop_back();
            rt.pop_back();

            cerr << opcode << " " << rd << " " << shift_amount << " " << rt << endl;
            output_file << inst_to_code[opcode] << register_addresses[rd] << to_binary_string(shift_amount, 4)
                        << register_addresses[rt] << "0000\n";

        } else if (opcode == "beq" or opcode == "bneq") {
            ss >> rs >> rt >> immediate;
            rs.pop_back();
            rt.pop_back();

            cerr << opcode << " " << rs << " " << rt << " " << immediate << endl;
            output_file << inst_to_code[opcode] << register_addresses[rs] << register_addresses[rt]
                        << to_binary_string(immediate, 8) << "\n";
        } else if (opcode == "j") {
            ss >> immediate;

            cerr << opcode << " " << immediate << endl;
            output_file << inst_to_code[opcode] << to_binary_string(immediate, 8) << endl;
        } else if (opcode == "sw" or opcode == "lw") {
            auto parsed_res = parse_memreadwrite(str);
            rt = parsed_res[1];
            rd = parsed_res[3];
            immediate = to_int(parsed_res[2]);

            cerr << opcode << " " << rt << " " << rs << immediate << endl;
            output_file << inst_to_code[opcode] << register_addresses[rt] << register_addresses[rs]
                        << to_binary_string(immediate, 8) << endl;
        } else {
            cerr << opcode << endl;
            //cerr << "opcode not identified.\n";
        }
    }

    input_file.close();
    output_file.close();
    format_output();

    return 0;
}
