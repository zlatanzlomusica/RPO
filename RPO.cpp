#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct History
{
    int style = 1;
    int txtLen = 0;
};
History loadHistory()
{
    History h;
    ifstream in("history.txt");
    if (in) in >> h.style >> h.txtLen;
    if (h.style < 1 || h.style > 5) h.style = 1;
    return h;
}
void saveHistory(int style, int txtLen)
{
    ofstream out("history.txt");
    if (out) out << style << ' ' << txtLen << '\n';
}

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

void centreText(vector<string>& canvas, const string& text) //Attempt at fixing aligment issue
{
    if (canvas.empty()) return;
    size_t mid = canvas.size() / 2;
    string& line = canvas[mid];

    size_t total = line.size();
    size_t len = text.size();

    if (len >= total) {
        line = text.substr(0, total);
        return;
    }
    size_t pad = (total - len) / 2;
    line.replace(pad, len, text);
}

void saveFile(const vector<string>& lines)
{
    ofstream out("output.txt");
    for (auto& l : lines) out << l << '\n';
    cout << "\nSaved to output.txt\n";
}

int main()
{
    const vector<pair<string, vector<string>(*)(const string&)>> styles = {
        {"Heart",   buildHeart},
        {"Arrow",   buildArrow},
        {"Diamond", buildDiamond},
        {"Banner",  buildBanner},
        {"Star",    buildStar}
    };

    History h = loadHistory();

    cout << "Pick a style (last used " << h.style << "):\n";
    for (size_t i = 0; i < styles.size(); ++i)
        cout << "  " << (int(i + 1) == h.style ? ">" : " ")
        << i + 1 << ") " << styles[i].first << '\n';

    int choice;
    cout << "Enter 1-" << styles.size() << " (0 = keep last): ";
    if (!(cin >> choice) || choice < 0 || choice > 5) choice = h.style;
    if (choice == 0) choice = h.style;

    cin.ignore();
    cout << "Enter your text: ";
    string text;
    getline(cin, text);

    vector<string> canvas = styles[choice - 1].second(text);
    centreText(canvas, text);

    cout << '\n';
    for (auto& l : canvas) cout << l << '\n';

    saveFile(canvas);
    saveHistory(choice, static_cast<int>(text.size()));
    return 0;
}

