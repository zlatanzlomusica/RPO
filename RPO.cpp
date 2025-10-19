/*
 *  ASCII Text Styler – centred frames, works everywhere
 *  g++ -std=c++17 -O2 text_styler.cpp -o text_styler
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* ---------- builders return the *frame* as ASCII lines ---------- */
vector<string> buildHeart(const string&)
{
    return {
        "  .-----------------------.  ",
        " / \\                     / \\ ",
        "(   )                   (   )",
        " \\ /                     \\ / ",
        "  '-----------------------'  "
    };
}

vector<string> buildArrow(const string&)
{
    return {
        "       /\\           ",
        "      /  \\          ",
        "     /    \\         ",
        "    /      \\        ",
        "   /        \\       ",
        "  /__________\\      ",
        "       ||           ",
        "       ||           "
    };
}

vector<string> buildDiamond(const string&)
{
    return {
        "     /\\     ",
        "    /  \\    ",
        "   /    \\   ",
        "  /      \\  ",
        " <        > ",
        "  \\      /  ",
        "   \\    /   ",
        "    \\  /    ",
        "     \\/     "
    };
}

vector<string> buildBanner(const string&)
{
    return {
        ".---------------------------.",
        "|                           |",
        "|                           |",
        "|                           |",
        "'---------------------------'"
    };
}

vector<string> buildStar(const string&)
{
    return {
        "     .-.     ",
        "   __| |__   ",
        "  /  .-.  \\  ",
        " |  /   \\  | ",
        "  \\  '-'  /  ",
        "   '--!--'   ",
        "     / \\     ",
        "    /   \\    "
    };
}

/* ---------- centre text inside the shape ---------- */
void centreText(vector<string>& canvas, const string& text)
{
    size_t h = canvas.size();
    if (h == 0) return;
    size_t mid = h / 2;

    string& line = canvas[mid];
    size_t total = line.size();
    size_t textLen = text.size();

    if (textLen >= total) {            // too long – truncate
        line = text.substr(0, total);
        return;
    }

    size_t pad = (total - textLen) / 2;
    line.replace(pad, textLen, text);
}



/* ---------- save ---------- */
void saveFile(const vector<string>& lines)
{
    ofstream out("output.txt");
    for (auto& l : lines) out << l << '\n';
    cout << "\nSaved to output.txt – open in Notepad to verify alignment.\n";
}

/* ---------- main ---------- */
int main()
{
    const vector<pair<string, vector<string>(*)(const string&)>> styles = {
        {"Heart",   buildHeart},
        {"Arrow",   buildArrow},
        {"Diamond", buildDiamond},
        {"Banner",  buildBanner},
        {"Star",    buildStar}
    };

    cout << "Pick a style:\n";
    for (size_t i = 0; i < styles.size(); ++i)
        cout << "  " << i + 1 << ") " << styles[i].first << '\n';

    int choice;
    cout << "Enter 1-" << styles.size() << ": ";
    if (!(cin >> choice) || choice < 1 || (size_t)choice > styles.size()) {
        cerr << "Invalid choice.\n";
        return 1;
    }

    cin.ignore(); // flush newline left by >>
    cout << "Enter your text: ";
    string text;
    getline(cin, text);

    vector<string> canvas = styles[choice - 1].second(text);
    centreText(canvas, text);

    cout << "\nPreview:\n";
    for (auto& l : canvas) cout << l << '\n';

    saveFile(canvas);
    return 0;
}