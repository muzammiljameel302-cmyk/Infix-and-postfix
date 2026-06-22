// STEP 3: solve the postfix using a stack -> true or false
bool evaluate(vector<string> postfix, map<string,double>& sensors) {
    stack<double> st;

    for (string w : postfix) {
        if (!isOperator(w)) {
            st.push(getValue(w, sensors));
        } else if (w == "NOT") {
            double a = st.top(); st.pop();
            st.push(a == 0 ? 1 : 0);
        } else {
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            double r = 0;

            if (w == ">")  r = (a > b);
            else if (w == "<")  r = (a < b);
            else if (w == ">=") r = (a >= b);
            else if (w == "<=") r = (a <= b);
            else if (w == "==") r = (a == b);
            else if (w == "!=") r = (a != b);
            else if (w == "AND") r = (a && b);
            else if (w == "OR")  r = (a || b);

            st.push(r);
        }
    }

    return st.top() != 0;
}
