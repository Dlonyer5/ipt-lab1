from rest_framework.routers import DefaultRouter
from .views import LibraryViewSet

router = DefaultRouter()
router.register(r'library', LibraryViewSet)

urlpatterns = router.urls