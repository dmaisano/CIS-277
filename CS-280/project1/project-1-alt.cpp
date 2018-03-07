#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm> // count()
using namespace std;

bool qflag, sflag, cflag, pflag, lflag;

typedef enum { unknown, wordish, spaceish } wordmode_t;

int main( int argc, char *argv[] ) {
  for( int n = 1; n < argc; n++) {
    if( argv[n][0] != '-' ) continue;
    string arg( argv[n] );
    if(      arg == "-q" ) qflag=true;
    else if( arg == "-s" ) sflag=true;
    else if( arg == "-c" ) cflag=true;
    else if( arg == "-p" ) pflag=true;
    else if( arg == "-l" ) lflag=true;
    else { cout << arg << " INVALID FLAG" << endl; return 1; }
  }

  bool foundfile=false;
  ifstream file;
  
  for( int n = 1; n < argc; n++ ) {
    if( argv[n][0] == '-' ) continue;
    if( foundfile ) { cout << "TOO MANY FILES" << endl; return 1; }
    foundfile=true;
    file.open(argv[n]);
    if( !file.is_open() ) { cout << argv[n] << " CANNOT OPEN" << endl; return 1; }
  }
 
  if( qflag && ( sflag || cflag ) ) {
    cout << "CONFLICTING FLAGS" << endl; return 1;
  }

  string wordstuff="", spacestuff="";
  bool isgood=true, isreal=true, iscap=true, isacronym=true;
  wordmode_t mode=unknown;
  char c='\0';
  int ncharsin=0, ncharsout=0, nlinesin=0, nlinesout=0,
  nwordsin=0, nwordsout=0, nreal=0, ngood=0, ncap=0, nacro=0;
  int maxlenword=0, maxlengood=0, maxlenreal=0;
  map<string,int> words, goodwords, realwords;

  while( foundfile ? file.get(c) : cin.get(c) ) {
    ncharsin++;
    if( c == '\n' ) nlinesin++;
    if( mode == unknown ) {
      if( isspace(c) ) { spacestuff+=c; mode=spaceish; continue; }
      
      // reset word stuff 
      isgood=true, isreal=true, iscap=true, isacronym=true;
      mode = wordish;
      if( !isupper(c) ) iscap=false;
    }
    else if( mode == wordish ) {
      if( isspace(c) ) { spacestuff=""; spacestuff+=c; mode=spaceish; continue; }
      // otherwise fall to the end of the if statement and do word stuff there
    }
    else if( mode == spaceish ) {
      if( isspace(c) ) { spacestuff+=c; continue; }
      // ok no longer a space but was just before - so we just started a word
     
      // now also keep track of whether it was a good/real/whatever
      int len=wordstuff.length();
      nwordsin++;  words[wordstuff]++; if( len>maxlenword ) maxlenword=len;
      
      if( isgood ) {
        ngood++; 
        goodwords[wordstuff]++;
        if( len > maxlengood ) maxlengood=len;
      }
      if( isreal ) {
        nreal++;
        realwords[wordstuff]++;
        if( len>maxlenreal )  maxlenreal=len;
      }
      if( iscap ) {
        ncap++;
      }
      if( isacronym ) {
        nacro++;
      }

      // first things first - decide whether to print out the word and the spaces we've collected so far
      if( qflag ) { /* do nothing */ }
      else if( ( cflag && isreal ) || !cflag ) {
        cout << wordstuff;
        nwordsout++;
        string printspace=spacestuff;

        if( sflag && spacestuff.length()>1) { 
          printspace = spacestuff[spacestuff.length()-1];
        }

        nlinesout += count(printspace.begin(), printspace.end(), '\n');
        cout << printspace;
        ncharsout += wordstuff.length()+printspace.length();
      }

      wordstuff="";
      spacestuff="";
       
      // now that we printed stuff (or not), reset word stuff 
      isgood=true, isreal=true, iscap=true, isacronym=true;
      mode = wordish;
      if( !isupper(c) ) iscap=false;
    }
   
    // after the if is definitely in word mode, no matter how we got here
    wordstuff  += c; 
    if( !isupper(c) ) isacronym=false;
    if( !isalnum(c) ) isgood=false;
    if( !isalpha(c) ) isreal=false;
  }

  // now also keep track of whether it was a good/real/whatever
  if( wordstuff != "" ) {
    int len=wordstuff.length();
    nwordsin++;  words[wordstuff]++; if( len>maxlenword ) maxlenword=len;
    if( isgood ) { 
      ngood++;
      goodwords[wordstuff]++;
      if( len > maxlengood ) maxlengood=len;
    }
    if( isreal ) {
      nreal++;
      realwords[wordstuff]++;
      if( len > maxlenreal )
      maxlenreal=len;
    }
    if( iscap ) {
      ncap++;
    }
    if( isacronym ) {
      nacro++;
    }
  }
  
  if( qflag ) { /* do nothing */ }
  else if( ( cflag && isreal ) || !cflag ) {
    cout << wordstuff;
    nwordsout++;
    string printspace=spacestuff;

    if( sflag && spacestuff.length() > 1) {
      printspace = spacestuff[spacestuff.length() - 1];
    }

    nlinesout += count(printspace.begin(), printspace.end(), '\n');
    cout << printspace;
    ncharsout+=wordstuff.length()+printspace.length();
  }
 
  // now also do the stats and lengths things for PART3
  if( pflag ) {
    cout << "Characters " << ncharsin << " in " << ncharsout << " out" << endl;
    cout << "Lines "      << nlinesin << " in " << nlinesout << " out" << endl;
    cout << "Words "      << nwordsin << " in " << nwordsout << " out" << endl;
    cout << "Goodwords "  << ngood    << " in"  << endl; 
    cout << "Realwords "  << nreal    << " in"  << endl;
    cout << "Capwords "   << ncap     << " in"  << endl;
    cout << "Acronyms "   << nacro    << " in"  << endl;
  }

  if( lflag ) {
    vector<string> w, g, r;
    for( const pair<string,int>& it :     words ) if( maxlenword==(signed)it.first.length() ) w.push_back(it.first);
    for( const pair<string,int>& it : goodwords ) if( maxlengood==(signed)it.first.length() ) g.push_back(it.first);
    for( const pair<string,int>& it : realwords ) if( maxlenreal==(signed)it.first.length() ) r.push_back(it.first);

    cout << "Word (length " << maxlenword << "): ";
    for( string s : w )
      cout << s << ( s==w.back() ? "" : ", " ); cout <<endl;

    cout << "Goodword (length " << maxlengood << "): ";
    for( string s : g )
      cout << s << ( s==g.back() ? "" : ", " ); cout <<endl;

    cout << "Realword (length " << maxlenreal << "): ";
    for( string s : r )
      cout << s << ( s==r.back() ? "" : ", " );cout <<endl;
  }

  return 0;
}
