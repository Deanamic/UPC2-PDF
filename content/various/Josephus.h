/**
 * Author: UPC
 * Date: ???
 * License: ???
 * Source: UPC pdf
 * Description: if you have n people in a circle and the first person to die is 0, and each time afterwards you kill the person k positions later, outputs the number of the last person to die
 * Status: tested
 */
#pragma once
cin >> n >> k; v[1]=0;
for (int i=2;i<=n;++i) v[i]=(v[i-1]+k)%i;
cout<< v[n]+1 << endl;
