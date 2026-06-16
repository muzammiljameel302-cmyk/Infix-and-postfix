// Run one rule and turn the device ON or OFF
void runRule(string device, string rule, map<string,double>& sensors) {
    vector<string> words = splitWords(rule);
    vector<string> postfix = toPostfix(words);

    cout << "\n--- " << device << " ---\n";
    cout << "Rule (Infix): " << rule << "\n";
    cout << "Postfix : ";
    for (string w : postfix) cout << w << " ";
    cout << "\n";

    bool on = evaluate(postfix, sensors);

    cout << "Result : " << (on ? "TRUE" : "FALSE") << "\n";
    cout << device << " is turned " << (on ? "ON" : "OFF") << "\n";
}
