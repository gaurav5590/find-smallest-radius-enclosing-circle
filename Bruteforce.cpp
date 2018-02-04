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
int main()
{
	cout<<setprecision(6)<<fixed;
	point  p1(0, 0), p2(0, 4), p3(2, 6);

	int i,n,j,k,l,count=0,count2=0,count3=0;
	circle c2(p1,p2,p3);
	circle c1(p1,p2,p3);
	double x,y;
	cin>>n;
	array<point> P(1,n);
	for(i=1;i<=n;i++)
	{
		cin>>x>>y;
		point p1(x,y);
		P[i]=p1;
	}
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			c1=circleoftwopoints(P[i],P[j]);
			for(l=1;l<=n;l++)
			{
				if(P[l].distance(c1.center())-c1.radius()<=1e-8)
					{
						count=count+1;
					}

			}
			if(count==n)
				{
					if(count2==0)
					{
						c2=c1;
					}
					else
					{
						if(c2.radius()>c1.radius())
						{
							c2=c1;
						}
						
					}
					count2=count2+1;
				}
				count=0;
		}
	}
	count=0;
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			for(k=j+1;k<=n;k++)
			{
				c1=circleofthreepoints(P[i],P[j],P[k]);
				for(l=1;l<=n;l++)
				{
					if(P[l].distance(c1.center())-c1.radius()<=1e-8)
					{
						count=count+1;
					}

				}
				if(count==n)
				{
					if(count2==0)
					{

						c2=c1;
					}
					else
					{
						if(c2.radius()>c1.radius())
						{
							c2=c1;
						}
						
					}
					count2=count2+1;
				}
				/*cout<<i<<","<<j<<","<<k<<endl;
				cout<<"C1:"<<c1.center()<<c1.radius()<<","<<count<<endl;
				cout<<"C2:"<<c2.center()<<c2.radius()<<","<<count<<endl;*/

				count=0;	
			}
		}
	}
	if(count2!=0)
	{
		double m= c2.center().xcoord();
		double p=c2.center().ycoord();
		cout  << m <<","<< p << endl<< c2.radius()<<endl ;

	}
	else
		{
			cout<<"No circle found"<<endl;
		}
	/*for(i=1;i<=n;i++)
	{
		if(P[i].distance(c2.center())-c2.radius()<=1e-8)
		{
			count=count+1;
		}
		
		
			cout<<P[i]<<P[i].distance(c2.center())-c2.radius()<<endl;
		
	}*/
	return 0;
}
