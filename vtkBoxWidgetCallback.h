#include "vtkCommand.h"
#include "vtkBoxWidget.h"
#include "vtkPlanes.h"

#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeRayCastMapper.h>

class vtkBoxWidgetCallback : public vtkCommand
{
	public:
	static vtkBoxWidgetCallback *New()
	{ return new vtkBoxWidgetCallback; }
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
		if (this->lowQuality)
		{
			vtkPlanes *planes = vtkPlanes::New();
			widget->GetPlanes(planes);
			this->smartMapper->SetClippingPlanes(planes);
			planes->Delete();
		}
		else
		{
			vtkPlanes *planes = vtkPlanes::New();
			widget->GetPlanes(planes);
			this->volumeMapper->SetClippingPlanes(planes);
			planes->Delete();
		}
	}
	void SetSmartMapper(vtkSmartVolumeMapper* m)
	{ this->smartMapper = m; this->lowQuality = true; }

	void SetVolumeMapper(vtkVolumeRayCastMapper* m)
	{ this->volumeMapper = m; this->lowQuality = false; }

	void SetLowQuality(bool quality)
	{ this->lowQuality = quality; }
   
	protected:
	vtkBoxWidgetCallback()
	{ 
		this->smartMapper = 0; 
		this->volumeMapper = 0;
		lowQuality = false;
	}
   
	vtkSmartVolumeMapper *smartMapper;
	vtkVolumeRayCastMapper *volumeMapper;
	bool lowQuality;
};
