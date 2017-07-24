
#define _RELEASE(A)			if((A)!=NULL) {(A)->Release( ); (A)=NULL;}  
#define _DELETE_ARRAY(A)	if((A)!=NULL) {delete [ ](A); (A)=NULL;}
#define _DELETE(A)			if((A)!=NULL) {delete (A); (A)=NULL;}

#ifndef POINTER_64

#if !defined(_MAC) && (defined(_M_MRX000) || defined(_M_AMD64) || defined(_M_IA64)) && (_MSC_VER >= 1100) && !(defined(MIDL_PASS) || defined(RC_INVOKED))
#define POINTER_64 __ptr64
typedef unsigned __int64 POINTER_64_INT;
#if defined(_WIN64)
#define POINTER_32 __ptr32
#else
#define POINTER_32
#endif
#else
#if defined(_MAC) && defined(_MAC_INT_64)
#define POINTER_64 __ptr64
typedef unsigned __int64 POINTER_64_INT;
#else
#if (_MSC_VER >= 1300) && !(defined(MIDL_PASS) || defined(RC_INVOKED))
#define POINTER_64 __ptr64
#else
#define POINTER_64
#endif
typedef unsigned long POINTER_64_INT;
#endif
#define POINTER_32
#endif
#endif

#include <map>
using namespace std;

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d8.h>
#include <d3dx8math.h>
#include <ddraw.h>


#include "Model\BaseEntity.h"
#include "Model\MovableEntity.h"
#include "Model\Hero.h"
#include "Model\Enemy.h"
#include "Model\Obstacle.h"
#include "Model\LogicModule.h"

#include "View\DXModule.h"
#include "View\GridMapRenderer.h"
#include "View\EnemyRenderer.h"
#include "View\HeroRenderer.h"
#include "View\ObstacleRenderer.h"
#include "View\GraphicsModule.h"

#include "Controller\InputModule.h"
#include "SystemModule.h"

