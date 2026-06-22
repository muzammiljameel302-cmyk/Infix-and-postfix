vector<string> splitWords(string rule) {
    vector<string> words;
    stringstream ss(rule);
    string word;

    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}
int main() {
    // Sensor Data Input
    map<string,double> sensors;
    sensors["temperature"] = 32;
    sensors["motion"] = 1;
    sensors["light_level"] = 25;
    sensors["time"] = 1900;

    // User Rules Input
    string fanRule =
        "temperature > 30 AND motion == 1";

    string lightRule =
        "light_level < 40 OR time > 1800";

    // Tokenization
    vector<string> fanTokens = splitWords(fanRule);
    vector<string> lightTokens = splitWords(lightRule);

    return 0;
}
