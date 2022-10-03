bool isWhiteSpace(char character){
    if (character == ' ')
        return true;
    if (character == '\r')
        return true;
    if (character == '\n')
        return true;
    return false;
}
//void parseInt(char input){
//    if (arrayOfIntsIndex >= arrayOfIntsLen){
//        return;
//    }
//    int value = atoi(input);
//    arrayOfInts[arrayOfIntsIndex] = value;
//    arrayOfIntsIndex++;
//}
