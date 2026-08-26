Se testeaza cum se modifica spectrul fotonilor care ajung la un detector virtual (la un anumit punct in spatiu) in functie de daca sursa este sau nu colimata. Se vede cantitativ cat de puternic influenteaza un colimator energia fotonilor care ajung la detectorul virtual (care poate fi de exemplu un debitmetru de doza de la hala).

- In "main.cc" se modifica nr. de evenimente per run.
- In "construction.hh" se modifica collimatedGeom in true sau false dupa caz (cu sau fara colimator).
- In "run.cc" se modifica nr. bini, E_min si E_max din spectru.
- In "gps.mac" se modifica energia gammelor.
