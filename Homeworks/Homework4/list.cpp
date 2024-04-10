//
//  list.cpp
//  Homework4P4
//
//  Created by Devansh Mishra on 05/03/24.
//

#include <stdio.h>

void listAll(string path, const Domain* d) // two-parameter overload
{
    if (d->subdomains().empty()) {
        cout << path << endl;
        return;
    }

    for (vector<Domain*>::const_iterator it = d->subdomains().begin(); it != d->subdomains().end(); it++) {
        if (path.empty()) {
            listAll((*it)->label(), (*it));
        }
        else {
            listAll((*it)->label() + "." + path, (*it));
        }
    }
}
