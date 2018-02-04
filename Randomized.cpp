#include <LEDA/geo/circle.h>
#include <LEDA/geo/point.h>
#include <iostream>
using namespace std;
using leda:: circle;
using leda:: point;
using leda:: array;
using leda:: segment;
circle circleoftwopoints(point p1,point p2)
{
	point p((p1.xcoord()+p2.xcoord())/2,(p1.ycoord()+p2.ycoord())/2);
	circle c1(p,(p1).distance(p2)/2);
	return c1;

}
circle circleofthreepoints(point p1,point p2,point p3)
{
	int count=0;
	point p((p1.xcoord()+p2.xcoord())/2,(p1.ycoord()+p2.ycoord())/2);
	circle c1(p,(p1).distance(p2)/2);
	circle c2(p,(p1).distance(p2)/2);
	if(p3.distance(c1.center())-c1.radius()<=1e-8)
	{
		count=1;
	}
	c1=circleoftwopoints(p1,p3);
	 if(p2.distance(c1.center())-c1.radius()<=1e-8)
	{
		if(count==0)
		{
			c2=c1;
			count=1;
		}
		else
		{
			if(c1.radius()<c2.radius())
			{
				c2=c1;
			}
		}
	}
	c1=circleoftwopoints(p2,p3);
	 if(p1.distance(c1.center())-c1.radius()<=1e-8)
	{
		if(count==0)
		{
			c2=c1;
			count=1;
		}
		else
		{
			if(c1.radius()<c2.radius())
			{
				c2=c1;
			}
		}
	}
	circle c3(p1,p2,p3);
	if(count==0)
		{
			c2=c3;
			count=1;
		}
		else
		{
			if(c3.radius()<c2.radius())
			{
				c2=c3;
			}
		}
	return c2;
}
circle CircleWithTwoBoundaryPoints(array<point> P,int k,point b0,point b1)
{
	array<circle> C(0,k);
	point p((b0.xcoord()+b1.xcoord())/2,(b0.ycoord()+b1.ycoord())/2);
	circle c1(p,(b0).distance(b1)/2);
	C[0]=c1;
	int i;
	for(i=1;i<=k;i++)
	{
		if(P[i].distance(C[i-1].center())-C[i-1].radius()<=1e-8)
			{
				C[i]=C[i-1];
			}
		else
			{
				C[i]=circleofthreepoints(b0,b1,P[i]);
			}
	}
	return C[k];
}
circle CircleWithSingleBoundaryPoint(array<point> P,int j,point b0)
{
	array<circle> C(1,j);
	point p((P[1].xcoord()+b0.xcoord())/2,(P[1].ycoord()+b0.ycoord())/2);
	circle c1(p,(P[1]).distance(b0)/2);
	C[1]=c1;
	int i;
	for(i=2;i<=j;i++)
	{
		if(P[i].distance(C[i-1].center())-C[i-1].radius()<=1e-8)
			{
				C[i]=C[i-1];
			}
		else
			{
				C[i]=CircleWithTwoBoundaryPoints(P,i-1,b0,P[i]);
			}
	}
	return C[j];
}

int main()
{
	cout<<setprecision(6)<<fixed;
	point  p1(0, 0), p2(0, 4), p3(2, 6);
	int n,i,j,k,l,count=0;
	double x,y;
	cin >> n;
	array<point> P(1,n);
	array<circle> C(1,n);
	for(i=1;i<=n;i++)
	{
		cin >>x>>y;
		point p1(x,y);
		P[i]=p1;
	}
	P.permute();
	//cout<<P[1]<<P[2]<<P[3]<<P[4]<<P[5]<<endl;
	if(n>=2)
	{
		point p((P[1].xcoord()+P[2].xcoord())/2,(P[1].ycoord()+P[2].ycoord())/2);
		circle c1(p,(P[1]).distance(P[2])/2);
		C[2]=c1;
		for(i=3;i<=n;i++)
		{
			if(P[i].distance(C[i-1].center())-C[i-1].radius()<=1e-8)
			{
				C[i]=C[i-1];
			}
			else
			{
				C[i]=CircleWithSingleBoundaryPoint(P,i-1,P[i]);
			}
		}
	}
	double m= C[n].center().xcoord();
	double p=C[n].center().ycoord();
	cout  << m <<","<< p << endl<< C[n].radius()<<endl ;
	/*for(i=1;i<=n;i++)
	{
		if(P[i].distance(C[n].center())-C[n].radius()<=1e-8)
		{
			count=count+1;
		}
		
		
			cout<<P[i]<<P[i].distance(C[n].center())<<endl;
		
	}
	cout<<count<<endl;*/
	return 0;
}